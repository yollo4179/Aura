// copyright



#include "Character/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	m_pWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	m_pWeapon->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	m_pWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);




}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
 UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent()const 
{
	 return m_pAbilitySystemComponent;
}

