// copyright

#pragma once
#include "GameplayEffectTypes.h"
#include"Delegates/DelegateCombinations.h"
#include "CoreMinimal.h"
#include "UI/WidgetController/MH_WidgetController.h"
#include "OverlayWidgetController.generated.h"


USTRUCT(BlueprintType)
struct FUIWidgetTableRow :public FTableRowBase //Drop�������� DT�� �ο� ��Ű�� 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();//SrcTag; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ExplainMassage = FText();
	UPROPERTY(EditAnywhere, BlueprintReadOnly) //CreateWidget �Ҷ� �ʿ��� 
	TSubclassOf<class UMH_UserWidget>MessgeWidgetClass = {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly) //CreateWidget �Ҷ� �ʿ��� 
	UTexture2D* Image = nullptr; 
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageWidgetRowDelegate, FUIWidgetTableRow, TagRow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeValueChangedSignature, float, NewAttributeValue);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UMH_WidgetController
{
	GENERATED_BODY()

public:
	
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies()override;



	UPROPERTY(BlueprintAssignable,Category ="Gas|Attributes")//��ε� ĳ��Ʈ�� �� ����
	FOnAttributeValueChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnAttributeValueChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnAttributeValueChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnAttributeValueChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes")
	FOnMessageWidgetRowDelegate MessageWidgetRowDelegate;

	

	//���̺���  ��Ű���� ������� �����ϱ����� ������ 
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "WidgetData")
	TObjectPtr<UDataTable> pMessageWidgetDT = {};

	

	template<typename T>
	T* GetUIWidgetTableRowByTag(const UDataTable* pTable , const FGameplayTag& Tag );
	
};

template<typename T>
inline T* UOverlayWidgetController::GetUIWidgetTableRowByTag(const UDataTable* pTable, const FGameplayTag& Tag)
{
	 return pTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
