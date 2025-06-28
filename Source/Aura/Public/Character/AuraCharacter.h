// copyright

#pragma once

#include"Interact/CombatInterface.h"
#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public ABaseCharacter 
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	
public:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual int32 GetCharacterLevel()override;
private:
	virtual void InitAbilityActorInfo()override;
};
