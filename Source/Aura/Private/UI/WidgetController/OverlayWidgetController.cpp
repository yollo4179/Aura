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

	//AttributeSet�� �ش�(���ϴ�) Attribute�� ���� ���Ҷ����� ȣ��Ǵ� ��������Ʈ�� ����Ѵ�. ��������Ʈ�̱� ������, Dynamic �� �ƴϱ⶧���� AddUObject()�� ���� �Լ��� ���ε��Ѵ�. 

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute())//��������Ʈ�� ����� ��Ʈ����Ʈ
		.AddUObject(this, &UOverlayWidgetController::HealthChanged);// ��������Ʈ ���ǿ� ������ �� ȣ���� �Լ� 
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute())//��������Ʈ�� ����� ��Ʈ����Ʈ
		.AddUObject(this, &UOverlayWidgetController::ManaChanged);// ��������Ʈ ���ǿ� ������ �� ȣ���� �Լ� 

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
