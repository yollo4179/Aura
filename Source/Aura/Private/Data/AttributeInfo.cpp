// copyright


#include "Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& GameplayTag, bool bLogNotFound) const
{

	for (const auto& Info : m_AttributeInfo)
	{
		if (Info.AttributeTag.MatchesTagExact(GameplayTag))
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag [%s] on AttributeInfo [%s]."), *GameplayTag.ToString(),*GetNameSafe(this));
	}
	return FAuraAttributeInfo(); 
}
