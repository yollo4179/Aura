// copyright


#include "UI/HUD/MH_HUD.h"
#include"UI/Widget/MH_UserWidget.h"
#include"UI/WidgetController/OverlayWidgetController.h"
#include"UI/WidgetController/AttributeMenuWidgetController.h"

void AMH_HUD::BeginPlay()
{
		Super::BeginPlay();
		// Initialize the HUD here if needed
}

UOverlayWidgetController* AMH_HUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	


	if (nullptr == OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		if (nullptr==OverlayWidgetController )
		{
			UE_LOG(LogTemp, Warning, TEXT("OverlayWidgetController is null! Check if it is set correctly."));
			return nullptr;
		}	
	
		OverlayWidgetController->SetWidgetComtrollerParams(Params);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AMH_HUD::GetAttMenuWidgetController(const FWidgetControllerParams& Params)
{
	if (nullptr == AttMenuWidgetController)
	{
		AttMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttMenuWidgetControllerClass);
		if (nullptr == AttMenuWidgetController)
		{
			UE_LOG(LogTemp, Warning, TEXT("OverlayWidgetController is null! Check if it is set correctly."));
			return nullptr;
		}

		AttMenuWidgetController->SetWidgetComtrollerParams(Params);
		AttMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttMenuWidgetController;
}

void AMH_HUD::InitOverlayWidgetController(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	
	checkf(OverlayWidgetClass, TEXT("There's no Widget class plaease fill put HUD with BP_WidgetClass"));
	checkf(OverlayWidgetControllerClass, TEXT("There's no Widget class plaease fill put HUD with BP_WidgetControllerClass"));


	UUserWidget* Widget =CreateWidget<UMH_UserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UMH_UserWidget>(Widget);

	



	FWidgetControllerParams Params(PC,PS,ASC,AS);

	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(Params);//GetWidgetController<UOverlayWidgetController>(Params, OverlayWidgetController, OverlayWidgetControllerClass);// GetOverlayWidgetController(Params);
	
	OverlayWidget->SetWidgetController(WidgetController);
	//오버레이 위젯에 SetWidgetController에서 컨트롤러를 초기화 할때,  WidgetControllSet 블루프린트 구현 함수가 여기서 호출된다. 
	//위젯 컨트롤러 델리게이트를 바인딩하는 좋은 타이밍 ( 컨트롤러는 PC,PS,ASC,AS) 를 모두 초기화해 가지고 있으며,
	// 오버레이 위젯은 컨트롤러를 가지고 있다

	//이 모든 과정이 끝난 후에야 비로소 오버레이 위젯 컨트롤러에게 델리게이트 초기값을 세팅할 수 있다.( 오버레이 위젯이 할 수 있는 것이 모두 다 보장되어 있으므로 )
	WidgetController->BroadcastInitialValues();

	if (Widget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget is null! Check if WidgetClass is set correctly."));
		return;
	}




	Widget->AddToViewport();

}
