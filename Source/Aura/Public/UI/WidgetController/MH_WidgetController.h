// copyright

#pragma once

class UAbilitySystemComponent;
class UAttributeSet;

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MH_WidgetController.generated.h"

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
public:

	FWidgetControllerParams() {};
	FWidgetControllerParams(
		APlayerController* PC,
		APlayerState* PS,
		UAbilitySystemComponent* ASC,
		UAttributeSet* AS
	):
		PlayerController(PC),
		PlayerState(PS),
		AbilitySystemComponent(ASC),
		AttributeSet(AS)
	{
	}

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<APlayerController> PlayerController = {};
	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<APlayerState> PlayerState = {};
	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr< UAbilitySystemComponent> AbilitySystemComponent = {};
	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr< UAttributeSet> AttributeSet = {};

};

/**
 * 
 */
UCLASS()
class AURA_API UMH_WidgetController : public UObject
{
	GENERATED_BODY()
public:
	UMH_WidgetController();

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetComtrollerParams(const FWidgetControllerParams& Params);


	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<APlayerController> PlayerController = {};

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<APlayerState> PlayerState = {};

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr< UAbilitySystemComponent> AbilitySystemComponent = {};

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr< UAttributeSet> AttributeSet = {};

};
