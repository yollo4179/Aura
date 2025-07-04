// copyright

#include "Character/EnemyCharacter.h"
#include"AbilitySystem/MH_AbilitySystemComponent.h"
#include"AttributeSet.h"
#include"AbilitySystemComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	m_pWeapon->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);


	
	m_pAbilitySystemComponent = CreateDefaultSubobject<UMH_AbilitySystemComponent>("Ability System Component");
	m_pAbilitySystemComponent->SetIsReplicated(true); // Enable replication for the ability system component
	m_pAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);// 표 참조하기

	m_pAttributeSet = CreateDefaultSubobject<UAttributeSet>("Attribute Set Enemy");
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
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	m_pAbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UMH_AbilitySystemComponent>(m_pAbilitySystemComponent)
		->AbilityActorInfoSet();
}