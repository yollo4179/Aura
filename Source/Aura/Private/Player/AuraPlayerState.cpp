// copyright
#include"AbilitySystem/MH_AbilitySystemComponent.h"
#include"AbilitySystem/MH_AttributeSet.h"

#include"AttributeSet.h"
#include"AbilitySystemComponent.h"
#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	m_pAbilitySystemComponent = CreateDefaultSubobject<UMH_AbilitySystemComponent>("Ability System Component");
	m_pAbilitySystemComponent->SetIsReplicated(true); // Enable replication for the ability system component
	m_pAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);// 표 참조하기

	m_pAttributeSet = CreateDefaultSubobject<UMH_AttributeSet>("Attribute Set");
	

	NetUpdateFrequency = 100.f; // Set a high update frequency for player state to ensure smooth gameplay updates
}
UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const 
{
	return m_pAbilitySystemComponent;
}