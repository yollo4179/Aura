// copyright

#include"AbilitySystemBlueprintLibrary.h"

#include"AbilitySystem/MH_AttributeSet.h"
#include"Player/AuraPlayerState.h"
#include"Character/AuraCharacter.h"
#include "Actor/MH_EffectActor.h"
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

	
}




void AMH_EffectActor::ApplayEffectToTarget(AActor* _pTarget, TSubclassOf<UGameplayEffect> _EffectClass)
{

	//Componrent 가져오기AttributeSet 가져오기 EffectContextHandle//가져오기-> 이펙스 스펙 핸들 가져오기 -> 적용함수 부르기 

	UAbilitySystemComponent* pTargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(_pTarget);//컴포넌트로 등록된 asc찾음

	if (pTargetASC == nullptr) return;
		
	check(_EffectClass);// 이거는 무조건 설정해줘야함 블루프린트 사이드에서

	FGameplayEffectContextHandle EffectContextHandle = pTargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);//이펙트 컨텍스트에 소스 오브젝트로 나를 추가한다. (내가 이텍트 Causer이다) 


	FGameplayEffectSpecHandle EffectSpecHandle = pTargetASC->MakeOutgoingSpec(_EffectClass, 1.0f, EffectContextHandle);
	//이펙트 스펙 핸들 생성 (레벨은 1.0f로 고정)// 이펙트 문맥을 설정한 후에 실제 이펙트에 접근할 수 있는 핸들을 생성한다.
	//핸들은 Wrapper고 Data는 스마트포인터여서 가비지 컬렉션이 되지 않는다. 역참조로 Spec을 직접 접근할 수 있다 
	
	pTargetASC->ApplyGameplayEffectSpecToSelf(*(EffectSpecHandle.Data.Get()));


}

