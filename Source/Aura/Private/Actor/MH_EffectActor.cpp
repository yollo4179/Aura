// copyright

#include "Actor/MH_EffectActor.h"
#include"AbilitySystemBlueprintLibrary.h"
#include"AbilitySystem/MH_AttributeSet.h"
#include"Player/AuraPlayerState.h"
#include"Character/AuraCharacter.h"
#include "Components/SphereComponent.h"



// Sets default values
AMH_EffectActor::AMH_EffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root Scene"));//씬컴포넌트로 위치만 설정하고 나머지 부착은 디자이너한테 맡긴다.




}

// Called when the game starts or when spawned
void AMH_EffectActor::BeginPlay()
{
	Super::BeginPlay();

	if (0 == EffectPool.Num())
	{
		CreateEffectPool();
	}
	
}




void AMH_EffectActor::ApplyEffectToTarget(AActor* _pTargetActor, TSubclassOf<UGameplayEffect> _EffectClass)
{

	//Componrent 가져오기AttributeSet 가져오기 EffectContextHandle//가져오기-> 이펙스 스펙 핸들 가져오기 -> 적용함수 부르기 

	UAbilitySystemComponent* pTargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(_pTargetActor);//컴포넌트로 등록된 asc찾음

	if (pTargetASC == nullptr) return;
		
	check(_EffectClass);// 이거는 무조건 설정해줘야함 블루프린트 사이드에서

	FGameplayEffectContextHandle EffectContextHandle = pTargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);//이펙트 컨텍스트에 소스 오브젝트로 나를 추가한다. (내가 이텍트 Causer이다) 


	const FGameplayEffectSpecHandle EffectSpecHandle = pTargetASC->MakeOutgoingSpec(_EffectClass, fEffectActorLevel, EffectContextHandle);
	//이펙트 스펙 핸들 생성 (레벨은 1.0f로 고정)// 이펙트 문맥을 설정한 후에 실제 이펙트에 접근할 수 있는 핸들을 생성한다.
	//핸들은 Wrapper고 Data는 스마트포인터여서 가비지 컬렉션이 되지 않는다. 역참조로 Spec을 직접 접근할 수 있다 
	

	/*Infinite 인 경우에 Endoverlap일 경우 지속 효과에서 벗어나게 하고 싶다. */
	FActiveGameplayEffectHandle pActiveGameplayActiveHandle = pTargetASC->ApplyGameplayEffectSpecToSelf(*(EffectSpecHandle.Data.Get()));

	//Spec은 Data.Get() Def.Get이UGameEffect이다.
	if (false == bDestroyOnEffectRemoval)
	{
		ActiveEffectHandles.Add(pActiveGameplayActiveHandle, pTargetASC);
	}
	else
	{
		Destroy();
		//EffectActor를 삭제한다.(Infinite Actor 가 아니면( 영원히 존재하는 장판같은게 아니면) ,item처럼 EndOverlap이 호출 될 일이 없는것  
	}

}

void AMH_EffectActor::ApplyEffectOnBeginOverlap(AActor* pTargetActor)// Overlap 발생 시에만 호출
{
	if (!pTargetActor) return;

	for (const auto& PoolingEffect : EffectPool)
	{
		if (eEffectApplicationPolicy::ApplyOnOverlap == PoolingEffect.EffectApplicationPolicy)
		{
			ApplyEffectToTarget(pTargetActor, PoolingEffect.GameplayEffectClass);// 내가가진 많은 효과들 중 이효과를 적용
		}
	}

}
//For Infinite
void AMH_EffectActor::ApplyEffectOnEndOverlap(AActor* pTargetActor) //EndOverlap 발생시에만 호출 
{
	for (const auto& PoolingEffect : EffectPool)
	{
		if (eEffectApplicationPolicy::ApplyOnEndOverlap == PoolingEffect.EffectApplicationPolicy)
		{
			ApplyEffectToTarget(pTargetActor, PoolingEffect.GameplayEffectClass);// 내가가진 많은 효과들 중 이효과를 적용
		}
	}
}
//For Infinite
void AMH_EffectActor::RemoveEffectsOnEndOverlap(AActor* pTargetActor)
{
	if (0 >= ActiveEffectHandles.Num())return; //기한이 Infinite인 것들만 들어간다. 
	if (0 >= EffectPool.Num())return;
	if (!pTargetActor)return;

	UAbilitySystemComponent* pTargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(pTargetActor);
	if (!IsValid(pTargetASC))return;

	TArray<FActiveGameplayEffectHandle>HandlesToRemove;

	for (const TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*>& InfiniteEffecPair : ActiveEffectHandles)
	{
		if (InfiniteEffecPair.Value != pTargetASC)continue; 
		
		HandlesToRemove.Add(InfiniteEffecPair.Key);// 지울 목록에 추가 
		
		pTargetASC->RemoveActiveGameplayEffect(InfiniteEffecPair.Key, 1);//타겟에 적용되고 있는 효과 제거 Handke Ref -1
	}

	for (const auto& HandleToRemove : HandlesToRemove)
	{
		ActiveEffectHandles.FindAndRemoveChecked(HandleToRemove);
	}
	

}

void AMH_EffectActor::RemoveEffect(AActor* pTargetActor)
{
	if (nullptr == pTargetActor)return;
	if ( 0 == EffectPool.Num() ) return;
	
}


void AMH_EffectActor::CreateEffectPool()
{

	//내가 가진 이펙트 들을 사전에 모두 모아놓는다. 
	
	//BeginPlay에서 호출 충돌전에 세팅
	if (0 < InstantEffects.Num())
	{
		for (const auto& InstantEffect : InstantEffects)
		{
			
			EffectPool.Add(
						FEffectPoolData{
							InstantEffect.EffectClass,
							InstantEffect.eApplicationPolicy,
						});
		}
	}


	if (0 < DurationEffects.Num())
	{
		for (const auto& DurationEffect : DurationEffects){
			EffectPool.Add(
				FEffectPoolData{
					DurationEffect.EffectClass,
					DurationEffect.eApplicationPolicy,
					DurationEffect.eEffectRemovalPolicy
				});
		}
	}

	if (0 < InfiniteEffects.Num())
	{
		for (const auto& InfiniteEffect : InfiniteEffects) {
			EffectPool.Add(
				FEffectPoolData{
					InfiniteEffect.EffectClass,
					InfiniteEffect.eApplicationPolicy,
					InfiniteEffect.eEffectRemovalPolicy
				});
		}
	}



}


