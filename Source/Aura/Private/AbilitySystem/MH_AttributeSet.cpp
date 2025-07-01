// copyright

#include "AbilitySystem/MH_AttributeSet.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"


UMH_AttributeSet::UMH_AttributeSet()
{
	this;
	//�����ڿ��� ��Ʈ����Ʈ�� �ʱ�ȭ �ϴ� ���� ����ϴ°��� �ƴ�
	InitHealth(10);
	InitMana(10.f);
	

	//1 ������ ���̺�� �ϴ� ���, 
	//2 . ���� �÷��� ����Ʈ�� �ϴ� �����
	//���� �÷��� ����Ʈ�� �ϴ� ����� ������ ���̽��� �е� , ���� �Ľ��ؼ� �е��� ���� ���� ����̴� . 

}

//4. ��Ʈ��ũ ����ȭ�� ���ؼ� �Ӽ� ������ �����ϴ� �Լ�
void UMH_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{


	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//��Ƽ�÷��̰��ӿ��� �÷��̾��� �ɷ�ġ�� ����Ǹ� �������� Ŭ���̾�Ʈ�� ���۵Ǿ�� �Ѵ�.(���ø�����Ʈ)
	
	/*Primary */
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	

#pragma region Second Abilities

	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	
#pragma endregion

	//�� �Ӽ��� ��Ʈ��ũ ������ ���� //�� �Ӽ����� �׻� ��Ʈ��ũ�� ����, �� ���� �� ���� �߻�
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Mana, COND_None, REPNOTIFY_Always);

	
	

}

void UMH_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	

	FEffectProperties SrcProperties= {};
	SetEffectProperties(Data, SrcProperties);

	if (GetHealthAttribute() == Data.EvaluatedData.Attribute)
	{
		SetHealth( FMath::Clamp(GetHealth(),0,GetMaxHealth()));
	}

	if (GetManaAttribute() == Data.EvaluatedData.Attribute)
	{
		SetMana(FMath::Clamp(GetMana(), 0, GetMaxMana()));
	}
}
//Attribute �� �ٲ�⸸ �ϸ� �Ҹ��� �Լ� Ȥ�� ����Ʈ ���� �Ŀ� �����÷��� ����Ʈ�κ��� ȣ��ȴ�. modifier �� ������� 
// // modifier �� ������ ������� �����ϴ°� -> post���� ����Ʈ ���� �Ŀ� �����ϴ°��� �����ϴ�.
void UMH_AttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const {

	this;
	Super::PreAttributeBaseChange(Attribute, NewValue);

		//if (Attribute == GetHealthAttribute())
		//{
		//	NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());//ALFL �̸� Ŭ����
		//
		//}
		//if (Attribute == GetManaAttribute())
		//{
		//	NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		//}

	
};


void UMH_AttributeSet::OnRep_Health(const FGameplayAttributeData& _OldHelth) const
{
	//Ŭ���̾�Ʈ���� �����κ��� ���ø�����Ʈ�� �Ӽ��� ���� �޾��� �� ȣ��ȴ�.
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.

	//Health �Ӽ��� ������ ó���ϰ� �ʿ��� UI������Ʈ�� ���ӷ����� Ʈ������ �� �ִ�-> �⺻���� ���ø� ���̼� �ൿ�� ����
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Health, _OldHelth);
}
void UMH_AttributeSet::OnRep_Mana(const FGameplayAttributeData& _OldMana) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Mana, _OldMana);
}



#pragma region Secondary

void UMH_AttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const 
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Armor, OldArmor);
}

void UMH_AttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UMH_AttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, BlockChance, OldBlockChance);
}

void UMH_AttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UMH_AttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UMH_AttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UMH_AttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UMH_AttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, ManaRegeneration, OldManaRegeneration);
}
void UMH_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& _OldMaxHealth) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, MaxHealth, _OldMaxHealth);
}

void UMH_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, MaxMana, OldMaxMana);
}
//Secondary Attribute�� Primary Attribute�� �������谡 �ִٸ� primary�� �ٲ𶧸��� Infinite GameplayEffect�� ���ؼ� �������踦 ������ش�.
#pragma endregion Secondary


#pragma region Primary
void UMH_AttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Strength, OldStrength);
}

void UMH_AttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Intelligence, OldIntelligence);
}

void UMH_AttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Resilience, OldResilience);
}

void UMH_AttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Vigor, OldVigor);
}
#pragma region Primary
void UMH_AttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Prop)//Src
{
	// Source == Causer of Effect( Attacker)  
	// Target (Defender)  == Target Of The Effect (Owner of this AS)



	FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* pSourceASC = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	Prop.EffectContextHandle = EffectContextHandle;
	Prop.pSrcASC = pSourceASC;


	if (IsValid(Prop.pSrcASC) &&
		Prop.pSrcASC->AbilityActorInfo.IsValid() &&
		Prop.pSrcASC->AbilityActorInfo.Get()->AvatarActor.IsValid()
		)
	{


		//�ϴ� �ƹ�Ÿ�� ������ �߻��� ����̴� State�� �ƴϴ�.  
		AActor* pSrcAvatarActor = pSourceASC->AbilityActorInfo.Get()->AvatarActor.Get();
		AController* pSrcController = pSourceASC->AbilityActorInfo.Get()->PlayerController.Get();
		Prop.pSrcAvatarActor = pSrcAvatarActor;
		Prop.pSrcController = pSrcController;

		//AbilityInfo �� �÷��̾� ��Ʈ�ѷ������� NULLPTR�� �Ǿ��ִٸ�,  Pawn���� ĳ�����ؼ� Actor�κ��� �ٷ� ��Ʈ�ѷ��� �����´� 
		if (nullptr == Prop.pSrcController && nullptr != Prop.pSrcAvatarActor)
		{
			if (APawn* pSrcPawn = Cast<APawn>(Prop.pSrcAvatarActor))
			{

				Prop.pSrcController = Cast<AController>(pSrcPawn->GetController());

			}
		}

		if (pSrcController)
		{
			ACharacter* pSrcCharacter = Cast<ACharacter>(pSrcController->GetCharacter());
			Prop.pSrcCharacter = pSrcCharacter;
		}
	}


	UAbilitySystemComponent* pTargetASC = &Data.Target;

	Prop.pTargetASC = pTargetASC;



	if (Data.Target.AbilityActorInfo.IsValid() &&
		Data.Target.AbilityActorInfo.Get()->AvatarActor.IsValid()
		)
	{
		AActor* pTargetActor = Data.Target.AbilityActorInfo.Get()->AvatarActor.Get();
		AController* pTargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		ACharacter* pTargetCharacter = pTargetController->GetCharacter();

		Prop.pTargetAvatarActor = pTargetActor;
		Prop.pTargetCharacter = pTargetCharacter;
		Prop.pTargetController = pTargetController;


	}
}
