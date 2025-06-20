// copyright

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent; 
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();

	class UAttributeSet* GetAttributeSet() const { return m_pAttributeSet; };
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY()
	TObjectPtr< UAttributeSet> m_pAttributeSet = {};
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> m_pAbilitySystemComponent = {};
};
