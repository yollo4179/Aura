// copyright

#pragma once
#include"AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MH_AttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class AURA_API UMH_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UMH_AttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY( BlueprintReadOnly,ReplicatedUsing =OnRep_Health ,Category="Vital Attributes")
	FGameplayAttributeData m_Health;
	ATTRIBUTE_ACCESSORS(UMH_AttributeSet, m_Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData m_MaxHealth;
	ATTRIBUTE_ACCESSORS(UMH_AttributeSet, m_MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Mana Attributes")
	FGameplayAttributeData m_Mana;
	ATTRIBUTE_ACCESSORS(UMH_AttributeSet, m_Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Mana Attributes")
	FGameplayAttributeData m_MaxMana;
	ATTRIBUTE_ACCESSORS(UMH_AttributeSet, m_MaxMana);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& _OldHelth)const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& _OldMaxHealth)const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& _OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& _OldMaxMana)const;
	
};
