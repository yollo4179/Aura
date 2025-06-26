// copyright


#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/MH_AttributeSet.h"
#include "GameplayEffectExtension.h"


UMH_AttributeSet::UMH_AttributeSet()
{
	InitHealth(10);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(100.f);

}

//4. ��Ʈ��ũ ����ȭ�� ���ؼ� �Ӽ� ������ �����ϴ� �Լ�
void UMH_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{


	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//��Ƽ�÷��̰��ӿ��� �÷��̾��� �ɷ�ġ�� ����Ǹ� �������� Ŭ���̾�Ʈ�� ���۵Ǿ�� �Ѵ�.(���ø�����Ʈ)
	
	//�� �Ӽ��� ��Ʈ��ũ ������ ���� //�� �Ӽ����� �׻� ��Ʈ��ũ�� ����, �� ���� �� ���� �߻�
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMH_AttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	
	

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


	Super::PreAttributeBaseChange(Attribute, NewValue);

		if (Attribute == GetHealthAttribute())
		{
			NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());//ALFL �̸� Ŭ����
		
		}
		if (Attribute == GetManaAttribute())
		{
			NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		}

	
};


void UMH_AttributeSet::OnRep_Health(const FGameplayAttributeData& _OldHelth) const
{
	//Ŭ���̾�Ʈ���� �����κ��� ���ø�����Ʈ�� �Ӽ��� ���� �޾��� �� ȣ��ȴ�.
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.

	//Health �Ӽ��� ������ ó���ϰ� �ʿ��� UI������Ʈ�� ���ӷ����� Ʈ������ �� �ִ�-> �⺻���� ���ø� ���̼� �ൿ�� ����
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Health, _OldHelth);
}

void UMH_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& _OldMaxHealth) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, MaxHealth, _OldMaxHealth);
}

void UMH_AttributeSet::OnRep_Mana(const FGameplayAttributeData& _OldMana) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Mana, _OldMana);
}

void UMH_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& _OldMaxMana) const
{
	// ���ø�����Ʈ�� �Ӽ��� ���� ����Ǹ� �� �Լ��� ȣ��ȴ�.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, MaxMana, _OldMaxMana);
}

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
