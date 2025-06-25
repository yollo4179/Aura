// copyright


#include "AbilitySystem/MH_AbilitySystemComponent.h"

void UMH_AbilitySystemComponent::AbilityActorInfoSet()
{

	//Aura Chracter ��  Enemy Character ��� SetAbilityActorInfo�� ȣ���ؼ� Avartar Actor Owner Actor ������ ä���� �Ŀ� 
	// Delegate Binding���� ������  ASC ���� ������ �� �ִ�( �����۾���) 

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMH_AbilitySystemComponent::EffectApplied);//�� ASC�� ����� ����ɶ�����  effectApplied �Լ��� ȣ��
}


void UMH_AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActoveEffectHandle)
{

	//AssetTag�� ����Ʈ�� ����Ǵ� ���Ϳ� �ο����� ���� 
	//Granted �±״� duration EFFECT���� ����


	//Tag�� GameplayTagContainaer�� ����ȴ� TArray���� ȿ����
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	OnEffectAssetTagDelegate.Broadcast(TagContainer);//Controller�� �Ѹ���.
	//�ش� ��������Ʈ�� ���ε�� Ŭ������ Broad CAST�� ������ �޴´� .->controller�� ���ε� �ʿ�


	//����� Effect�� ���� ��� tag�� ��ε�ĳ��Ʈ -> �������Ʈ�ּ� ��Ȯ
	for (const FGameplayTag& Tag : TagContainer)
	{

	}

	//��� ������ �±׸� ���ؼ� BroadCast�� ������ �˵��� (UI)���� ��Ʈ�ѷ��� �ѷ��ִ� �۾��� �ϰ� �ʹ�. 


	//GEngine->AddOnScreenDebugMessage(1,8.f, FColor::Red, FString("Applied"));
}
