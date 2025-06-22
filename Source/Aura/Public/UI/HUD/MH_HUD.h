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


};
//HUD�� ���� ��Ʈ�ѷ��� �����ϰ�, OVERRAY ������ �����ϴ� ���� ������ġ
