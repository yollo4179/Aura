// copyright


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
