// copyright


#include "UI/Widget/MH_UserWidget.h"

//#include"UI/WidgetController/OverlayWidgetController.h"
//#include"AbilitySystem/MH_AbilitySystemComponent.h"



void UMH_UserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

