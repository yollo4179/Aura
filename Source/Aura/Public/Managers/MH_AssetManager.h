// copyright

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MH_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMH_AssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UMH_AssetManager& Get();

protected:
	//ó�� ���� �ε��Ҷ� ȣ��Ǵϱ� �̶� �±� ����ϸ� ���̴� . 
	virtual void StartInitialLoading()override;
private:
	
};
