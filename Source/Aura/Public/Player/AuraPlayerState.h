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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	class UAttributeSet* GetAttributeSet() const  { return m_pAttributeSet; };
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE	int32 GetCharacterLevel() { return Level; };
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr< UAttributeSet> m_pAttributeSet = {};

	//AttribuSetting 을 DataTable을 통해서 하기 위해서 VisibleANYSWERE-> 디태일 패널의 Attribute Test 에 값 세팅
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAbilitySystemComponent> m_pAbilitySystemComponent = {};


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Level, Category = "Primary Attributes")
	int32 Level = { 3 };
	UFUNCTION()
	void OnRep_Level(const int32& OldLevel)const;
};
