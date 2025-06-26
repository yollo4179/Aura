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

//4. 네트워크 동기화를 위해서 속성 복제를 설정하는 함수
void UMH_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{


	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//멀티플레이게임에서 플레이어의 능력치가 변경되면 서버에서 클라이언트로 전송되어야 한다.(레플리케이트)
	
	//각 속성의 네트워크 복제를 설정 //이 속성들은 항상 네트워크에 복제, 값 변경 시 통지 발생
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
//Attribute 가 바뀌기만 하면 불리는 함수 혹은 이펙트 연산 후에 게임플레이 이펙트로부터 호출된다. modifier 가 결과리턴 
// // modifier 의 쿼링한 결과에서 수정하는것 -> post에서 이펙트 실행 후에 적용하는것이 적법하다.
void UMH_AttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const {


	Super::PreAttributeBaseChange(Attribute, NewValue);

		if (Attribute == GetHealthAttribute())
		{
			NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());//ALFL 미리 클램프
		
		}
		if (Attribute == GetManaAttribute())
		{
			NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
		}

	
};


void UMH_AttributeSet::OnRep_Health(const FGameplayAttributeData& _OldHelth) const
{
	//클라이언트에서 서버로부터 레플리케이트된 속성의 값을 받았을 때 호출된다.
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.

	//Health 속성의 변경을 처리하고 필요한 UI업데이트나 게임로직을 트리거할 수 있다-> 기본젇인 이플리 케이션 행동을 구현
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Health, _OldHelth);
}

void UMH_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& _OldMaxHealth) const
{
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, MaxHealth, _OldMaxHealth);
}

void UMH_AttributeSet::OnRep_Mana(const FGameplayAttributeData& _OldMana) const
{
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMH_AttributeSet, Mana, _OldMana);
}

void UMH_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& _OldMaxMana) const
{
	// 레플리케이트된 속성의 값이 변경되면 이 함수가 호출된다.
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
