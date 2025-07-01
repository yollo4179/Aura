// copyright
#include "Player/AuraPlayerState.h"
#include"AbilitySystem/MH_AbilitySystemComponent.h"
#include"AbilitySystem/MH_AttributeSet.h"
#include"AttributeSet.h"
#include"AbilitySystemComponent.h"
#include"Net/UnrealNetwork.h"


AAuraPlayerState::AAuraPlayerState()
{
	this;
	m_pAbilitySystemComponent = CreateDefaultSubobject<UMH_AbilitySystemComponent>("AbilitySystemComponent");
	m_pAbilitySystemComponent->SetIsReplicated(true); // Enable replication for the ability system component
	m_pAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);// 표 참조하기

	m_pAttributeSet = CreateDefaultSubobject<UMH_AttributeSet>("AttributeSet");
	

	NetUpdateFrequency = 100.f; // Set a high update frequency for player state to ensure smooth gameplay updates
	this;
}
UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const 
{
	
	return m_pAbilitySystemComponent;
}
void AAuraPlayerState::OnRep_Level(const int32& OldLevel)const
{

}
void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAuraPlayerState, Level);

}