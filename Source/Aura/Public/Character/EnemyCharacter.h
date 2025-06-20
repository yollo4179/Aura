// copyright

#pragma once

#include"Interact/EnemyInterface.h"
#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "EnemyCharacter.generated.h"


#define DEPTH_STENCIL_HIGHLIGHT_RED 250
/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ABaseCharacter , public IEnemyInterface
{

	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void HighlightActor() override;

	virtual void UnHighlightActor() override;

	virtual void BeginPlay() override;
	
};
