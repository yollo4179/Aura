// copyright


#include "Managers/TagManager.h"
#include"GameplayTagsManager.h"
CTagManager CTagManager::m_TagManager;//�̱��� ( ����)������ ȣ��, �ʱ�ȭ 

void CTagManager::InitializeNativeGameplayTags()
{

	//���� ����� �����Ҽ� �����Ƿ�  ����ƽ��������� ����� ������ ����, �������� �±׿� ����԰� ���ÿ� �±׸� ����� ���� ( �̱��濡 ���� _ 
	m_TagManager.InitPrimaryTags();
	m_TagManager.InitSecondaryTags();
	return;
}

void CTagManager::AddTag(const FName& Key, const FString& Value)
{
	m_GameplayTags.Add(
		Key
		, UGameplayTagsManager::Get().AddNativeGameplayTag(Key, Value)
	);
}

const FGameplayTag& CTagManager::GetTag(const FName& Key)
{
	
	return m_GameplayTags.FindChecked(Key);
}

void CTagManager::InitSecondaryTags()
{


	AddTag(FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves Block Chance"));

	AddTag(FName("Attributes.Secondary.ArmorPenetration"), 
		FString("Ignores Percentage of enemy Armor, increases Critical Hit Chance"));
	
	AddTag(FName("Attributes.Secondary.BlockChance"), 
		FString("Chance to cut incoming damage in half"));

	AddTag(FName("Attributes.Secondary.CriticalHitChance"), 
		FString("Chance to double damage plus critical hit bonus"));
	
	AddTag(FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Bonus damage added when a critical hit is scored"));
	
	AddTag(FName("Attributes.Secondary.CriticalHitResistance"), 
		FString("Reduces Critical Hit Chance of attacking enemies"));
	
	AddTag(FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of Health regenerated every 1 second"));
	
	AddTag(FName("Attributes.Secondary.ManaRegeneration"), 
		FString("Amount of Mana regenerated every 1 second"));
	
	AddTag(FName("Attributes.Secondary.MaxHealth"), 
		FString("Maximum amount of Health obtainable"));
	
	AddTag(FName("Attributes.Secondary.MaxMana"), 
		FString("Maximum amount of Mana obtainable"));
}

void CTagManager::InitPrimaryTags()
{

	AddTag(FName("Attributes.Primary.Strength"),
		FString("Increases physical damage"));

	AddTag(FName("Attributes.Primary.Intelligence"), 
		FString("Increases magical damage"));

	AddTag(FName("Attributes.Primary.Resilience"),
		FString("Increases Armor and Armor Penetration"));

	AddTag(FName("Attributes.Primary.Vigor"),
		FString("Increases Health"));
}
