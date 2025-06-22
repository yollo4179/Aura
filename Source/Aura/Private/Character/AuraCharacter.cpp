// copyright
#include"Player/AuraPlayerController.h"
#include"UI/HUD/MH_HUD.h"
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
	
	//캐릭터에서 이거 회전 조작하면 안되다.
	bUseControllerRotationPitch = false; 
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//InitAbility actor info for the Server
	InitAbilityActorInfo();	
	/*여기서 하면 될거 같은데? HUD 초기화! (Player State, asc,as 모두 끝났음을 보장 )*/
	/*PlayerController는? ->GameMode 설정할때 바인딩했으므로 존재*/

}
void AAuraCharacter::OnRep_PlayerState()
{

	Super::OnRep_PlayerState();
	//InitAbility actor info for the client
	InitAbilityActorInfo();

}

void AAuraCharacter::InitAbilityActorInfo()
{

	AAuraPlayerState* pPlayerState = GetPlayerState<AAuraPlayerState>();//State 만들어줌 
	check(pPlayerState);
	pPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(pPlayerState, this);//Player를 Controller가 자동으로 소유하도록 설정
	m_pAbilitySystemComponent = pPlayerState->GetAbilitySystemComponent();
	m_pAttributeSet = pPlayerState->GetAttributeSet();


	/*Hud에 접근하기 위해서 PlayerController 를 가져온다 */


	AAuraPlayerController* pController =Cast<AAuraPlayerController>(GetController());

	if (pController)
	{
		AMH_HUD* pHUD =Cast<AMH_HUD>(pController->GetHUD());

		pHUD->InitOverlayWidgetController(pController,pPlayerState,m_pAbilitySystemComponent, m_pAttributeSet);
	}
}
