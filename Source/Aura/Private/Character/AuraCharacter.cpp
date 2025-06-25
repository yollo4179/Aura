// copyright

#include "Character/AuraCharacter.h"
#include"Player/AuraPlayerController.h"
#include"UI/HUD/MH_HUD.h"
#include"Player/AuraPlayerState.h"
#include"AbilitySystemComponent.h"
#include"AbilitySystem/MH_AbilitySystemComponent.h"
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
	/*���⼭ �ϸ� �ɰ� ������? HUD �ʱ�ȭ! (Player State, asc,as ��� �������� ���� )*/
	/*PlayerController��? ->GameMode �����Ҷ� ���ε������Ƿ� ����*/

}
void AAuraCharacter::OnRep_PlayerState()
{

	Super::OnRep_PlayerState();
	//InitAbility actor info for the client
	InitAbilityActorInfo();

}

void AAuraCharacter::InitAbilityActorInfo()
{
	//BP���� ������Ʈ�� ��Ʈ�ѷδ� ���Ӹ�忡 ���������Ƿ� �ű⼭ ������
	AAuraPlayerState* pPlayerState = GetPlayerState<AAuraPlayerState>();//State ������� 
	check(pPlayerState);
	pPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(pPlayerState, this);//Player�� Controller�� �ڵ����� �����ϵ��� ����
	
	Cast<UMH_AbilitySystemComponent>(pPlayerState->GetAbilitySystemComponent())
		->AbilityActorInfoSet();

	m_pAbilitySystemComponent = pPlayerState->GetAbilitySystemComponent();
	m_pAttributeSet = pPlayerState->GetAttributeSet();


	/*Hud�� �����ϱ� ���ؼ� PlayerController �� �����´� */

	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AMH_HUD* AuraHUD = Cast<AMH_HUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlayWidgetController(AuraPlayerController, pPlayerState, m_pAbilitySystemComponent, m_pAttributeSet);
		}
	}

}
