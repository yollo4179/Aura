// copyright


#include "UI/Widget/MH_UserWidget.h"





void UMH_UserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
