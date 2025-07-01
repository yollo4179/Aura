// copyright

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MH_BlueprintFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API UMH_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static class UOverlayWidgetController* GetOverlayWidgetController(UObject* WorldContextObject);// 
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|WidgetController")
	static class UAttributeMenuWidgetController* GetAttMenuWidgetController(UObject* WorldContextObject);// 
};
