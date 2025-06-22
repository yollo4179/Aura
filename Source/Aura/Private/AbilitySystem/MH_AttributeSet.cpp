// copyright


#include "Net/UnrealNetwork.h"
#include "AbilitySystem/MH_AttributeSet.h"

UMH_AttributeSet::UMH_AttributeSet()
{
	InitHealth(10);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(100.f);
}

void UMH_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//��Ƽ�÷��̰��ӿ��� �÷��̾��� �ɷ�ġ�� ����Ǹ� �������� Ŭ���̾�Ʈ�� ���۵Ǿ�� �Ѵ�.(���ø�����Ʈ)
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	

}
void UMH_AttributeSet::OnRep_Health(const FGameplayAttributeData& _OldHelth) const
{
	//Ŭ���̾�Ʈ���� �����κ��� ���ø�����Ʈ�� �Ӽ��� ���� �޾��� �� ȣ��ȴ�.
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Health, _OldHelth);
}

void UMH_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& _OldMaxHealth) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, MaxHealth, _OldMaxHealth);
}

void UMH_AttributeSet::OnRep_Mana(const FGameplayAttributeData& _OldMana) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Mana, _OldMana);
}

void UMH_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& _OldMaxMana) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, MaxMana, _OldMaxMana);
}
