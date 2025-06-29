// copyright


#include "Managers/MH_AssetManager.h"
#include"Managers/TagManager.h"
CAssetManager& CAssetManager::Get()
{
	check(GEngine);
	CAssetManager* AssetManager = Cast<CAssetManager>(GEngine->AssetManager);
	return (*AssetManager);
}
void CAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	CTagManager::InitializeNativeGameplayTags();

}