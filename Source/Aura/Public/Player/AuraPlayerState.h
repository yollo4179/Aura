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

	//AttribuSetting �� DataTable�� ���ؼ� �ϱ� ���ؼ� VisibleANYSWERE-> ������ �г��� Attribute Test �� �� ����
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAbilitySystemComponent> m_pAbilitySystemComponent = {};


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Level, Category = "Primary Attributes")
	int32 Level = { 3 };
	UFUNCTION()
	void OnRep_Level(const int32& OldLevel)const;
};
