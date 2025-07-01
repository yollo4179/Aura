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
	//�������� ������ SetWidgetController���� ��Ʈ�ѷ��� �ʱ�ȭ �Ҷ�,  WidgetControllSet �������Ʈ ���� �Լ��� ���⼭ ȣ��ȴ�. 
	//���� ��Ʈ�ѷ� ��������Ʈ�� ���ε��ϴ� ���� Ÿ�̹� ( ��Ʈ�ѷ��� PC,PS,ASC,AS) �� ��� �ʱ�ȭ�� ������ ������,
	// �������� ������ ��Ʈ�ѷ��� ������ �ִ�

	//�� ��� ������ ���� �Ŀ��� ��μ� �������� ���� ��Ʈ�ѷ����� ��������Ʈ �ʱⰪ�� ������ �� �ִ�.( �������� ������ �� �� �ִ� ���� ��� �� ����Ǿ� �����Ƿ� )
	WidgetController->BroadcastInitialValues();

	if (Widget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Widget is null! Check if WidgetClass is set correctly."));
		return;
	}




	Widget->AddToViewport();

}
