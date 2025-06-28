// copyright

#pragma once

#include"Interact/CombatInterface.h"
#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"
class UAttributeSet;
class UAbilitySystemComponent;
UCLASS(ABSTRACT)
class AURA_API ABaseCharacter : public ACharacter ,public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	UAttributeSet* GetAttributeSet() const { return m_pAttributeSet; };
	virtual  UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual int32 GetCharacterLevel() { return 0; };
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() {};

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> m_pWeapon = {};

	UPROPERTY()
	TObjectPtr< UAttributeSet> m_pAttributeSet = {};
	UPROPERTY()
	TObjectPtr< UAbilitySystemComponent> m_pAbilitySystemComponent = {};

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category= "Primary Attributes")
	TSubclassOf<class UGameplayEffect>m_PrimaryEffectClass;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Secondary Attributes")
	TSubclassOf<class UGameplayEffect>m_SecondaryEffectClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Secondary Attributes")
	TSubclassOf<class UGameplayEffect>m_VitalEffectClass;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffecClass,float Level)const ;
	void InitDefaultAttributes()const ; 
	


};
