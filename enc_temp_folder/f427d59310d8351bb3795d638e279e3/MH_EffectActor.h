// copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MH_EffectActor.generated.h"

UCLASS()
class AURA_API AMH_EffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMH_EffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	

	void ApplayEffectToTarget(AActor* _pTarget, TSubclassOf <class UGameplayEffect> _EffectClass);

private:

	UPROPERTY(EditAnywhere, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;


};
