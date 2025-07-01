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
	//처음 에셋 로딩할때 호출되니까 이때 태그 등록하면 딱이다 . 
	virtual void StartInitialLoading()override;
private:
	
};
