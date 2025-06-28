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
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root Scene"));//��������Ʈ�� ��ġ�� �����ϰ� ������ ������ �����̳����� �ñ��.




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

	//Componrent ��������AttributeSet �������� EffectContextHandle//��������-> ���彺 ���� �ڵ� �������� -> �����Լ� �θ��� 

	UAbilitySystemComponent* pTargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(_pTargetActor);//������Ʈ�� ��ϵ� ascã��

	if (pTargetASC == nullptr) return;
		
	check(_EffectClass);// �̰Ŵ� ������ ����������� �������Ʈ ���̵忡��

	FGameplayEffectContextHandle EffectContextHandle = pTargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);//����Ʈ ���ؽ�Ʈ�� �ҽ� ������Ʈ�� ���� �߰��Ѵ�. (���� ����Ʈ Causer�̴�) 


	const FGameplayEffectSpecHandle EffectSpecHandle = pTargetASC->MakeOutgoingSpec(_EffectClass, fEffectActorLevel, EffectContextHandle);
	//����Ʈ ���� �ڵ� ���� (������ 1.0f�� ����)// ����Ʈ ������ ������ �Ŀ� ���� ����Ʈ�� ������ �� �ִ� �ڵ��� �����Ѵ�.
	//�ڵ��� Wrapper�� Data�� ����Ʈ�����Ϳ��� ������ �÷����� ���� �ʴ´�. �������� Spec�� ���� ������ �� �ִ� 
	

	/*Infinite �� ��쿡 Endoverlap�� ��� ���� ȿ������ ����� �ϰ� �ʹ�. */
	FActiveGameplayEffectHandle pActiveGameplayActiveHandle = pTargetASC->ApplyGameplayEffectSpecToSelf(*(EffectSpecHandle.Data.Get()));

	//Spec�� Data.Get() Def.Get��UGameEffect�̴�.
	if (false == bDestroyOnEffectRemoval)
	{
		ActiveEffectHandles.Add(pActiveGameplayActiveHandle, pTargetASC);
	}
	else
	{
		Destroy();
		//EffectActor�� �����Ѵ�.(Infinite Actor �� �ƴϸ�( ������ �����ϴ� ���ǰ����� �ƴϸ�) ,itemó�� EndOverlap�� ȣ�� �� ���� ���°�  
	}

}

void AMH_EffectActor::ApplyEffectOnBeginOverlap(AActor* pTargetActor)// Overlap �߻� �ÿ��� ȣ��
{
	if (!pTargetActor) return;

	for (const auto& PoolingEffect : EffectPool)
	{
		if (eEffectApplicationPolicy::ApplyOnOverlap == PoolingEffect.EffectApplicationPolicy)
		{
			ApplyEffectToTarget(pTargetActor, PoolingEffect.GameplayEffectClass);// �������� ���� ȿ���� �� ��ȿ���� ����
		}
	}

}
//For Infinite
void AMH_EffectActor::ApplyEffectOnEndOverlap(AActor* pTargetActor) //EndOverlap �߻��ÿ��� ȣ�� 
{
	for (const auto& PoolingEffect : EffectPool)
	{
		if (eEffectApplicationPolicy::ApplyOnEndOverlap == PoolingEffect.EffectApplicationPolicy)
		{
			ApplyEffectToTarget(pTargetActor, PoolingEffect.GameplayEffectClass);// �������� ���� ȿ���� �� ��ȿ���� ����
		}
	}
}
//For Infinite
void AMH_EffectActor::RemoveEffectsOnEndOverlap(AActor* pTargetActor)
{
	if (0 >= ActiveEffectHandles.Num())return; //������ Infinite�� �͵鸸 ����. 
	if (0 >= EffectPool.Num())return;
	if (!pTargetActor)return;

	UAbilitySystemComponent* pTargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(pTargetActor);
	if (!IsValid(pTargetASC))return;

	TArray<FActiveGameplayEffectHandle>HandlesToRemove;

	for (const TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*>& InfiniteEffecPair : ActiveEffectHandles)
	{
		if (InfiniteEffecPair.Value != pTargetASC)continue; 
		
		HandlesToRemove.Add(InfiniteEffecPair.Key);// ���� ��Ͽ� �߰� 
		
		pTargetASC->RemoveActiveGameplayEffect(InfiniteEffecPair.Key, 1);//Ÿ�ٿ� ����ǰ� �ִ� ȿ�� ���� Handke Ref -1
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

	//���� ���� ����Ʈ ���� ������ ��� ��Ƴ��´�. 
	
	//BeginPlay���� ȣ�� �浹���� ����
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


