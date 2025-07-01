// copyright

#include "AbilitySystem/MH_AttributeSet.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"


UMH_AttributeSet::UMH_AttributeSet()
{
	this;
	//생성자에서 애트리뷰트를 초기화 하는 것은 우너하는것이 아님
	InitHealth(10);
	InitMana(10.f);
	

	//1 데이터 테이블로 하는 방법, 
	//2 . 게임 플레이 이펙트로 하느 ㄴ방법
	//게임 플레이 이펙트로 하는 방법이 데이터 베이스를 읽든 , 파일 파싱해서 읽든지 가장 편한 방법이다 . 

}

//4. 네트워크 동기화를 위해서 속성 복제를 설정하는 함수
void UMH_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{


	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//멀티플레이게임에서 플레이어의 능력치가 변경되면 서버에서 클라이언트로 전송되어야 한다.(레플리케이트)
	
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

	//각 속성의 네트워크 복제를 설정 //이 속성들은 항상 네트워크에 복제, 값 변경 시 통지 발생
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
//Attribute 가 바뀌기만 하면 불리는 함수 혹은 이펙트 연산 후에 게임플레이 이펙트로부터 호출된다. modifier 가 결과리턴 
// // modifier 의 쿼링한 결과에서 수정하는것 -> post에서 이펙트 실행 후에 적용하는것이 적법하다.
void UMH_AttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const {

	this;
	Super::PreAttributeBaseChange(Attribute, NewValue);

		//if (Attribute == GetHealthAttribute())
		//{
		//	NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());//ALFL 미리 클램프
		//
		//}
		//if (Attribute == GetManaAttribute())
		//{
		//	NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		//}

	
};


void UMH_AttributeSet::OnRep_Health(const FGameplayAttributeData& _OldHelth) const
{
	//클라이언트에서 서버로부터 레플리케이트된 속성의 값을 받았을 때 호출된다.
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.

	//Health 속성의 변경을 처리하고 필요한 UI업데이트나 게임로직을 트리거할 수 있다-> 기본젇인 이플리 케이션 행동을 구현
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Health, _OldHelth);
}
void UMH_AttributeSet::OnRep_Mana(const FGameplayAttributeData& _OldMana) const
{
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.
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
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, MaxHealth, _OldMaxHealth);
}

void UMH_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, MaxMana, OldMaxMana);
}
//Secondary Attribute는 Primary Attribute와 의존관계가 있다면 primary가 바뀔때마다 Infinite GameplayEffect를 통해서 의존관계를 만들어준다.
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


		//일단 아바타는 무조건 발사한 대상이다 State가 아니다.  
		AActor* pSrcAvatarActor = pSourceASC->AbilityActorInfo.Get()->AvatarActor.Get();
		AController* pSrcController = pSourceASC->AbilityActorInfo.Get()->PlayerController.Get();
		Prop.pSrcAvatarActor = pSrcAvatarActor;
		Prop.pSrcController = pSrcController;

		//AbilityInfo 가 플레이어 컨트롤러에대해 NULLPTR로 되어있다면,  Pawn으로 캐스팅해서 Actor로부터 바로 컨트롤러를 가져온다 
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
