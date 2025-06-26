// copyright

#pragma once
#include"AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MH_AttributeSet.generated.h"


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	UPROPERTY()
	UAbilitySystemComponent* pSrcASC = {};
	UPROPERTY()
	AActor* pSrcAvatarActor = {};
	UPROPERTY()
	AController* pSrcController = {}; 
	UPROPERTY()
	ACharacter* pSrcCharacter = {}; 


	UPROPERTY()
	UAbilitySystemComponent* pTargetASC = {};
	UPROPERTY()
	AActor* pTargetAvatarActor = {};
	UPROPERTY()
	AController* pTargetController = {};
	UPROPERTY()
	ACharacter* pTargetCharacter = {};


	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle = {};

};

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

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)override;

	virtual  void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	

	// 1. ReplicatedUsing로 레플리케이션 시에 호출될 콜백함수를 지정한다./ 변경시 호출
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMH_AttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMH_AttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMH_AttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMH_AttributeSet, MaxMana);





	//2. 네트워크를 통해 새로운 aTTRIBUTE 값이 도착하면 콜백함수를 선언한다. 
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& _OldHelth)const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& _OldMaxHealth)const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& _OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& _OldMaxMana)const;




private:
	void SetEffectProperties(const  FGameplayEffectModCallbackData& Data, FEffectProperties& Prop);

};