// copyright


#include "Managers/TagManager.h"
#include"GameplayTagsManager.h"
CTagManager CTagManager::m_TagManager;//싱글턴 ( 전역)생성자 호출, 초기화 

void CTagManager::InitializeNativeGameplayTags()
{

	//정적 멤버에 저장할수 없으므로  스테틱멤버변수의 멤버로 저장해 놓고, 에디터의 태그에 등록함과 동시에 태그를 멤버로 저장 ( 싱글톤에 의한 _ 
	m_TagManager.m_SecondaryAttributeArmorTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));

	return;
}
