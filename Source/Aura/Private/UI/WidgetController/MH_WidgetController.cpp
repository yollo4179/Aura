// copyright


#include "UI/WidgetController/MH_WidgetController.h"

UMH_WidgetController::UMH_WidgetController()
{
}

void UMH_WidgetController::SetWidgetComtrollerParams(const FWidgetControllerParams& Params)
{
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;

}

void UMH_WidgetController::BroadcastInitialValues()
{

}

void UMH_WidgetController::BindCallbacksToDependencies()
{
}
const UAbilitySystemComponent* UMH_WidgetController::GetAbilitySystemComponent()
{
	return AbilitySystemComponent; 
}
