// copyright

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MH_AbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsDelegate,const  FGameplayTagContainer& /*Asset(Src) Tags*/)
/**
 * 
 */
UCLASS()
class AURA_API UMH_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();


	FEffectAssetTagsDelegate OnEffectAssetTagDelegate;
protected:
	void EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActoveEffectHandle);

};
