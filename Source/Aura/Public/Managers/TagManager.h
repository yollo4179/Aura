// copyright
#pragma once

#include "CoreMinimal.h"
#include"GameplayTagContainer.h"
/**
 * 
 */
class AURA_API CTagManager
{
	#define TAGMAP	TMap<FName, FGameplayTag>
public:
	static CTagManager& Get() { return m_TagManager; };

	static void InitializeNativeGameplayTags();

	
	void AddTag(const FName& Key, const FString& Value);
	const FGameplayTag& GetTag(const FName& Key);
protected:

private:
	
	void InitSecondaryTags();
	void InitPrimaryTags();
	static CTagManager m_TagManager;
	TAGMAP m_GameplayTags;
	
};