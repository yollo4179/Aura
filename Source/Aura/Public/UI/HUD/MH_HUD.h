// copyright

#pragma once

class UOverlayWidgetController; 
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAttributeSet;

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MH_HUD.generated.h"

/**
 * 
 */

UCLASS()
class AURA_API AMH_HUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);
	class UAttributeMenuWidgetController* GetAttMenuWidgetController(const FWidgetControllerParams& Params);
	/*template<typename T>
	T* GetWidgetController(const FWidgetControllerParams& Params, TObjectPtr<T> pController, TSubclassOf<T>ControllerClass);*/


	void InitOverlayWidgetController(
		APlayerController*PC,
		APlayerState* PS,
		UAbilitySystemComponent* ASC,
		UAttributeSet* AS
	);
public: 

	
	
	UPROPERTY()
	TObjectPtr<class UMH_UserWidget> OverlayWidget; 
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMH_UserWidget>OverlayWidgetClass;
	

	UPROPERTY()
	TObjectPtr <UOverlayWidgetController> OverlayWidgetController = {};
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController>OverlayWidgetControllerClass;


	UPROPERTY()
	TObjectPtr < UAttributeMenuWidgetController> AttMenuWidgetController = {};
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController>AttMenuWidgetControllerClass;

};
//HUD가 위젯 컨트롤러를 관리하고, OVERRAY 위젯을 생성하는 가장 좋은위치

//template<typename T>
//inline T* AMH_HUD::GetWidgetController(const FWidgetControllerParams& Params, TObjectPtr<T> pController, TSubclassOf<T>ControllerClass)
//{
//	if (nullptr == pController)
//	{
//		pController = NewObject<T>(this, ControllerClass);
//		if (nullptr == pController)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("OverlayWidgetController is null! Check if it is set correctly."));
//			return nullptr;
//		}
//
//		pController->SetWidgetComtrollerParams(Params);
//		pController->BindCallbacksToDependencies();
//	}
//	return OverlayWidgetController;
//
//
//	return nullptr;
//}
