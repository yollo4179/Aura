// copyright

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"
class UAttributeSet;
class UAbilitySystemComponent;
UCLASS()
class AURA_API ABaseCharacter : public ACharacter ,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	UAttributeSet* GetAttributeSet() const { return m_pAttributeSet; };
	virtual  UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> m_pWeapon = {};

	UPROPERTY()
	TObjectPtr< UAttributeSet> m_pAttributeSet = {};
	UPROPERTY()
	TObjectPtr< UAbilitySystemComponent> m_pAbilitySystemComponent = {};

};
