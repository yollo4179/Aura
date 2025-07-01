// copyright

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MH_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UCAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UCAssetManager& Get();

protected:
	//ó�� ���� �ε��Ҷ� ȣ��Ǵϱ� �̶� �±� ����ϸ� ���̴� . 
	virtual void StartInitialLoading()override;
private:
	
};
