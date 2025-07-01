// copyright


#include "Managers/MH_AssetManager.h"
#include"Managers/TagManager.h"

UCAssetManager& UCAssetManager::Get()
{
	check(GEngine);
	UCAssetManager* AssetManager = Cast<UCAssetManager>(GEngine->AssetManager);
	return (*AssetManager);

	
}
void UCAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	CTagManager::InitializeNativeGameplayTags();

	
}