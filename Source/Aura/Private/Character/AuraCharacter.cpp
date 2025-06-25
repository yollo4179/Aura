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
	//BP에서 스테이트와 컨트롤로는 게임모드에 설정했으므로 거기서 가져옴
	AAuraPlayerState* pPlayerState = GetPlayerState<AAuraPlayerState>();//State 만들어줌 
	check(pPlayerState);
	pPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(pPlayerState, this);//Player를 Controller가 자동으로 소유하도록 설정
	
	Cast<UMH_AbilitySystemComponent>(pPlayerState->GetAbilitySystemComponent())
		->AbilityActorInfoSet();

	m_pAbilitySystemComponent = pPlayerState->GetAbilitySystemComponent();
	m_pAttributeSet = pPlayerState->GetAttributeSet();


	/*Hud에 접근하기 위해서 PlayerController 를 가져온다 */

	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AMH_HUD* AuraHUD = Cast<AMH_HUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlayWidgetController(AuraPlayerController, pPlayerState, m_pAbilitySystemComponent, m_pAttributeSet);
		}
	}

}
