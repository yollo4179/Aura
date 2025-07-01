// copyright


#include "AbilitySystem/MH_BlueprintFunctionLibrary.h"
//#include "MH_BlueprintFunctionLibrary.h"

#include"Kismet/GameplayStatics.h"
#include"UI/HUD/MH_HUD.h"
#include"Player/AuraPlayerController.h"
#include"Player/AuraPlayerState.h"
#include"AbilitySystem/MH_AbilitySystemComponent.h"

#include"UI/WidgetController/MH_WidgetController.h"


UOverlayWidgetController* UMH_BlueprintFunctionLibrary::GetOverlayWidgetController(UObject* WorldContextObject)
{

	if (AAuraPlayerController* PC= Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)))
	{
		if (AMH_HUD* pHUD = Cast<AMH_HUD>(PC->GetHUD()))
		{

			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();

			UMH_AbilitySystemComponent* ASC =Cast<UMH_AbilitySystemComponent>(PS->GetAbilitySystemComponent());

			UAttributeSet* AS = PS->GetAttributeSet();
			
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return pHUD->GetOverlayWidgetController(WidgetControllerParams);

		}
		

	}
	
   return nullptr;
}
UAttributeMenuWidgetController* UMH_BlueprintFunctionLibrary:: GetAttMenuWidgetController(UObject* WorldContextObject)
{

	if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)))
	{
		if (AMH_HUD* pHUD = Cast<AMH_HUD>(PC->GetHUD()))
		{

			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();

			UMH_AbilitySystemComponent* ASC = Cast<UMH_AbilitySystemComponent>(PS->GetAbilitySystemComponent());

			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return pHUD->GetAttMenuWidgetController(WidgetControllerParams);

		}


	}

	return nullptr;
};