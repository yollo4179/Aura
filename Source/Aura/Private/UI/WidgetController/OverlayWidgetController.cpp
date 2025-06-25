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

	//AttributeSet�� �ش�(���ϴ�) Attribute�� ���� ���Ҷ����� ȣ��Ǵ� ��������Ʈ�� ����Ѵ�. ��������Ʈ�̱� ������, Dynamic �� �ƴϱ⶧���� AddUObject()�� ���� �Լ��� ���ε��Ѵ�. 

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute())//��������Ʈ�� ����� ��Ʈ����Ʈ
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnHealthChanged.Broadcast(Data.NewValue);});//�� �̺�Ʈ ȣ���ؼ� �������Ʈ�� �˸��� �� ����});
	//AddUObject(this, &UOverlayWidgetController::HealthChanged);// ��������Ʈ ���ǿ� ������ �� ȣ���� �Լ� �ú� ���� ���ٷ� �ص���
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxHealthChanged.Broadcast(Data.NewValue); });

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetManaAttribute())//��������Ʈ�� ����� ��Ʈ����Ʈ
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnManaChanged.Broadcast(Data.NewValue); });// ��������Ʈ ���ǿ� ������ �� ȣ���� �Լ� 

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxManaChanged.Broadcast(Data.NewValue); });

	UMH_AbilitySystemComponent* CustomASC = Cast<UMH_AbilitySystemComponent>(AbilitySystemComponent);
	CustomASC->OnEffectAssetTagDelegate.AddLambda(
		[&](const FGameplayTagContainer& TagContainer)->void//BroadCast�Ŀ� ȣ��ɰ� (Effect ������ -> Tag BroadCast-> LAMDA�� ���ڷ� �±� ����
		{
			for (const auto& Tag : TagContainer)
			{
				//if (nullptr == pMessageWidgetDT);
				
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag("Message");// ���� ���ϴ� �ؽ�Ʈ�� Tagȭ ��Ų��. 
				if (Tag.MatchesTag(MessageTag)) {//Message �±װ� �ƴ϶��ó���� �±� �� �ƴϹǷ� x 
					//���� ���� �� �θ� �ش� �±װ� �´��� Ȯ���ϴ� �Լ�  
					FUIWidgetTableRow* pTableRow = GetUIWidgetTableRowByTag<FUIWidgetTableRow>(pMessageWidgetDT, Tag);
					MessageWidgetRowDelegate.Broadcast(*pTableRow);
				}
				//OnWidgetMessageRow.Broadcast(pTableRow);
				//�� Row ������ �������� �������Ѵ�. (�������� Broad Cast)
				/*const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *pTableRow->ExplainMassage.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);*/

			}
			
			
			
		}
	
	);

	
}