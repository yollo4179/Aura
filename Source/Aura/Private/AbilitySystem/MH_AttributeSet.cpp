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
	//멀티플레이게임에서 플레이어의 능력치가 변경되면 서버에서 클라이언트로 전송되어야 한다.(레플리케이트)
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, m_Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, m_MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, m_Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, m_MaxMana, COND_None, REPNOTIFY_Always);
	

}
void UMH_AttributeSet::OnRep_Health(const FGameplayAttributeData& _OldHelth) const
{
	//클라이언트에서 서버로부터 레플리케이트된 속성의 값을 받았을 때 호출된다.
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, m_Health, _OldHelth);
}

void UMH_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& _OldMaxHealth) const
{
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, m_MaxHealth, _OldMaxHealth);
}

void UMH_AttributeSet::OnRep_Mana(const FGameplayAttributeData& _OldMana) const
{
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, m_Mana, _OldMana);
}

void UMH_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& _OldMaxMana) const
{
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, m_MaxMana, _OldMaxMana);
}
