// copyright


#include "AbilitySystem/MH_AbilitySystemComponent.h"
#include"Managers/TagManager.h"
void UMH_AbilitySystemComponent::AbilityActorInfoSet()
{

	//Aura Chracter 나  Enemy Character 모두 SetAbilityActorInfo를 호출해서 Avartar Actor Owner Actor 정보를 채워준 후에 
	// Delegate Binding같은 적업을  ASC 에서 세팅할 수 있다( 공통작업들) 

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMH_AbilitySystemComponent::EffectApplied);//이 ASC에 료과가 적용될때마다  effectApplied 함수가 호출
	const FGameplayTag& pTag = CTagManager::Get().GetTag(FName("Attributes.Secondary.Armor"));
	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Orange,
		FString::Printf(TEXT("Tag :%s"), *(pTag.ToString()))
	);

}


void UMH_AbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActoveEffectHandle)
{

	//AssetTag는 이펙트가 적용되는 액터에 부여되지 않음 
	//Granted 태그는 duration EFFECT에만 적용


	//Tag는 GameplayTagContainaer에 저장된다 TArray보다 효과적
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	OnEffectAssetTagDelegate.Broadcast(TagContainer);//Controller에 뿌린다.
	//해당 델리게이트와 바인드된 클래스는 Broad CAST의 정보를 받는다 .->controller에 바인드 필요


	//적용된 Effect에 대한 모든 tag를 브로드캐스트 -> 블루프린트애서 수확
	for (const FGameplayTag& Tag : TagContainer)
	{

	}

	//모든 각각의 태그를 위해서 BroadCast로 위젯이 알도록 (UI)위젯 컨트롤러에 뿌려주는 작업을 하고 싶다. 


	//GEngine->AddOnScreenDebugMessage(1,8.f, FColor::Red, FString("Applied"));
}
