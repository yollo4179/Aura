// copyright

#pragma once
#include"Interact/CombatInterface.h"
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
	
	FORCEINLINE virtual int32 GetCharacterLevel() override { return Level; };

protected:
	virtual void BeginPlay() override;
	
	virtual void InitAbilityActorInfo()override;



	//���� ������ ��������üũ���Ұ��� - ���������۾��� ��������ó��(�÷��̾�� ���͵�), ���ø����̼� ���ϴ�����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Level")
	int32 Level = {};
};
