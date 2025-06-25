// copyright

#pragma once

#include"AbilitySystemComponent.h"
#include"AttributeSet.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MH_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMH_UserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();


public:
	


	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	

	
};
