// copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
protected:
	void BeginPlay()override;
	void SetupInputComponent()override;
public:
	virtual void PlayerTick(float DeltaTime)override;
	void CursorTrace();
private:

	UPROPERTY(EditAnywhere, Category= "Input")
	TObjectPtr<class UInputMappingContext>AuraContext = {};

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction = {};

	class IEnemyInterface* ThisActor = {};
	 IEnemyInterface* LastActor = {};
	void Move(const struct FInputActionValue& InputActionValue);



};
