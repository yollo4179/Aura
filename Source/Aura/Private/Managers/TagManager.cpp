// copyright


#include "Managers/TagManager.h"
#include"GameplayTagsManager.h"
CTagManager CTagManager::m_TagManager;//�̱��� ( ����)������ ȣ��, �ʱ�ȭ 

void CTagManager::InitializeNativeGameplayTags()
{

	//���� ����� �����Ҽ� �����Ƿ�  ����ƽ��������� ����� ������ ����, �������� �±׿� ����԰� ���ÿ� �±׸� ����� ���� ( �̱��濡 ���� _ 
	m_TagManager.m_SecondaryAttributeArmorTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));

	return;
}
