// copyright

#pragma once

#include "CoreMinimal.h"
#include"GameplayTagContainer.h"
/**
 * 
 */
class AURA_API CTagManager
{
public:
	const static CTagManager& Get() { return m_TagManager; };

	static void InitializeNativeGameplayTags();
protected:

private:
	FGameplayTag m_SecondaryAttributeArmorTag;
	static CTagManager m_TagManager;

};