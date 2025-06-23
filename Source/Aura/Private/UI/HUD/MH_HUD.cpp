// copyright

#include"UI/Widget/MH_UserWidget.h"
#include "UI/HUD/MH_HUD.h"
#include"UI/WidgetController/OverlayWidgetController.h"


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

void AMH_HUD::InitOverlayWidgetController(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	
	checkf(OverlayWidgetClass, TEXT("There's no Widget class plaease fill put HUD with BP_WidgetClass"));
	checkf(OverlayWidgetControllerClass, TEXT("There's no Widget class plaease fill put HUD with BP_WidgetControllerClass"));


	UUserWidget* Widget = CreateWidget<UMH_UserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UMH_UserWidget>(Widget);

	



	FWidgetControllerParams Params(PC,PS,ASC,AS);

	UOverlayWidgetController*  WidgetController = GetOverlayWidgetController(Params);
	
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
