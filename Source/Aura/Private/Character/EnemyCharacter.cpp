// copyright


#include "Character/EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	m_pWeapon->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AEnemyCharacter::UnHighlightActor()
{
	//IsHighlighted = false; 
	
	//IsHighlighted = true;
	GetMesh()->SetRenderCustomDepth(false);
	m_pWeapon->SetRenderCustomDepth(false);


}
void AEnemyCharacter::HighlightActor()
{
	

	//CollisionEnabledToFlags();
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(DEPTH_STENCIL_HIGHLIGHT_RED);
	m_pWeapon->SetRenderCustomDepth(true);
	m_pWeapon->SetCustomDepthStencilValue(DEPTH_STENCIL_HIGHLIGHT_RED);


}
