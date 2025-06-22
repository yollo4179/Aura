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
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root Scene"));//��������Ʈ�� ��ġ�� �����ϰ� ������ ������ �����̳����� �ñ��.




}

// Called when the game starts or when spawned
void AMH_EffectActor::BeginPlay()
{
	Super::BeginPlay();

	
}




void AMH_EffectActor::ApplayEffectToTarget(AActor* _pTarget, TSubclassOf<UGameplayEffect> _EffectClass)
{

	//Componrent ��������AttributeSet �������� EffectContextHandle//��������-> ���彺 ���� �ڵ� �������� -> �����Լ� �θ��� 

	UAbilitySystemComponent* pTargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(_pTarget);//������Ʈ�� ��ϵ� ascã��

	if (pTargetASC == nullptr) return;
		
	check(_EffectClass);// �̰Ŵ� ������ ����������� �������Ʈ ���̵忡��

	FGameplayEffectContextHandle EffectContextHandle = pTargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);//����Ʈ ���ؽ�Ʈ�� �ҽ� ������Ʈ�� ���� �߰��Ѵ�. (���� ����Ʈ Causer�̴�) 


	FGameplayEffectSpecHandle EffectSpecHandle = pTargetASC->MakeOutgoingSpec(_EffectClass, 1.0f, EffectContextHandle);
	//����Ʈ ���� �ڵ� ���� (������ 1.0f�� ����)// ����Ʈ ������ ������ �Ŀ� ���� ����Ʈ�� ������ �� �ִ� �ڵ��� �����Ѵ�.
	//�ڵ��� Wrapper�� Data�� ����Ʈ�����Ϳ��� ������ �÷����� ���� �ʴ´�. �������� Spec�� ���� ������ �� �ִ� 
	
	pTargetASC->ApplyGameplayEffectSpecToSelf(*(EffectSpecHandle.Data.Get()));


}

