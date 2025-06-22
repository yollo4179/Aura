// copyright

#include"AbilitySystem/MH_AttributeSet.h"
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
		.AddUObject(this, &UOverlayWidgetController::HealthChanged);// 델리게이트 조건에 만족할 때 호출할 함수 
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute())//델리게이트에 등록할 어트리뷰트
		.AddUObject(this, &UOverlayWidgetController::ManaChanged);// 델리게이트 조건에 만족할 때 호출할 함수 

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data)
{/*
	UMH_AttributeSet* AuraAttributeSet = CastChecked<UMH_AttributeSet>(AttributeSet);
	float fHelath = AuraAttributeSet->GetHealth();
	OnHealthChanged.Broadcast(fHelath);*/

	//==

	OnHealthChanged.Broadcast(Data.NewValue	);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
