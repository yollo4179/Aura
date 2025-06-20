// copyright


#include "Net/UnrealNetwork.h"
#include "AbilitySystem/MH_AttributeSet.h"

UMH_AttributeSet::UMH_AttributeSet()
{
	Initm_Health(100.f);
}

void UMH_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//��Ƽ�÷��̰��ӿ��� �÷��̾��� �ɷ�ġ�� ����Ǹ� �������� Ŭ���̾�Ʈ�� ���۵Ǿ�� �Ѵ�.(���ø�����Ʈ)
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, m_Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, m_MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, m_Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, m_MaxMana, COND_None, REPNOTIFY_Always);
	

}
void UMH_AttributeSet::OnRep_Health(const FGameplayAttributeData& _OldHelth) const
{
	//Ŭ���̾�Ʈ���� �����κ��� ���ø�����Ʈ�� �Ӽ��� ���� �޾��� �� ȣ��ȴ�.
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, m_Health, _OldHelth);
}

void UMH_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& _OldMaxHealth) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, m_MaxHealth, _OldMaxHealth);
}

void UMH_AttributeSet::OnRep_Mana(const FGameplayAttributeData& _OldMana) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, m_Mana, _OldMana);
}

void UMH_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& _OldMaxMana) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, m_MaxMana, _OldMaxMana);
}
