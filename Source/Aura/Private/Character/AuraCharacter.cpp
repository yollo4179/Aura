// copyright

#include"Player/AuraPlayerState.h"
#include"AbilitySystemComponent.h"
#include "Character/AuraCharacter.h"
#include"GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane= true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	//ĳ���Ϳ��� �̰� ȸ�� �����ϸ� �ȵǴ�.
	bUseControllerRotationPitch = false; 
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//InitAbility actor info for the Server
	InitAbilityActorInfo();	

}
void AAuraCharacter::OnRep_PlayerState()
{

	Super::OnRep_PlayerState();
	//InitAbility actor info for the client
	InitAbilityActorInfo();

}

void AAuraCharacter::InitAbilityActorInfo()
{

	AAuraPlayerState* pPlayerState = GetPlayerState<AAuraPlayerState>();//State ������� 
	check(pPlayerState);
	pPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(pPlayerState, this);
	m_pAbilitySystemComponent = pPlayerState->GetAbilitySystemComponent();
	m_pAttributeSet = pPlayerState->GetAttributeSet();


}
