// copyright

#include"AbilitySystem/MH_AttributeSet.h"
#include"AbilitySystem/MH_AbilitySystemComponent.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	UMH_AttributeSet* AuraAttributeSet = CastChecked<UMH_AttributeSet>(AttributeSet);
	float fHelath = AuraAttributeSet->GetHealth();
	OnHealthChanged.Broadcast(fHelath);

	float fMaxHelath = AuraAttributeSet->GetMaxHealth();
	OnMaxHealthChanged.Broadcast(fMaxHelath);


	float fMana = AuraAttributeSet->GetMana();
	OnManaChanged.Broadcast(fMana);

	float fMaxMana = AuraAttributeSet->GetMaxMana();
	OnMaxManaChanged.Broadcast(fMaxMana);




}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UMH_AttributeSet* AuraAttributeSet = CastChecked<UMH_AttributeSet>(AttributeSet);

	//AttributeSet의 해당(원하는) Attribute의 값이 변할때마다 호출되는 델리게이트를 등록한다. 델리게이트이긴 하지만, Dynamic 이 아니기때문에 AddUObject()를 통해 함수를 바인딩한다. 

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute())//델리게이트에 등록할 어트리뷰트
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnHealthChanged.Broadcast(Data.NewValue);});//이 이벤트 호출해서 블루프린트에 알린다 값 전달});
	//AddUObject(this, &UOverlayWidgetController::HealthChanged);// 델리게이트 조건에 만족할 때 호출할 함수 컬벡 말고 람다로 해도됨
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxHealthChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute())//델리게이트에 등록할 어트리뷰트
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnManaChanged.Broadcast(Data.NewValue); });// 델리게이트 조건에 만족할 때 호출할 함수 

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxManaChanged.Broadcast(Data.NewValue); });

	UMH_AbilitySystemComponent* CustomASC = Cast<UMH_AbilitySystemComponent>(AbilitySystemComponent);
	CustomASC->OnEffectAssetTagDelegate.AddLambda(
		[&](const FGameplayTagContainer& TagContainer)->void//BroadCast후에 호출될것 (Effect 적용후 -> Tag BroadCast-> LAMDA의 인자로 태그 전달
		{
			for (const auto& Tag : TagContainer)
			{
				//if (nullptr == pMessageWidgetDT);
				
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag("Message");// 내가 원하는 텍스트를 Tag화 시킨다. 
				if (Tag.MatchesTag(MessageTag)) {//Message 태그가 아니라면처리할 태그 가 아니므로 x 
					//계층 구조 상 부모가 해당 태그가 맞는지 확인하는 함수  
					FUIWidgetTableRow* pTableRow = GetUIWidgetTableRowByTag<FUIWidgetTableRow>(pMessageWidgetDT, Tag);
					MessageWidgetRowDelegate.Broadcast(*pTableRow);
				}
				//OnWidgetMessageRow.Broadcast(pTableRow);
				//이 Row 정보를 위젯으로 보내야한다. (위젯으로 Broad Cast)
				/*const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *pTableRow->ExplainMassage.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);*/

			}
			
			
			
		}
	
	);

	
}