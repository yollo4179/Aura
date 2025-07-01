// copyright

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/MH_WidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FAuraAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UMH_WidgetController
{
	GENERATED_BODY()
public:
	void BindCallbacksToDependencies()override;

	
	void BroadcastInitialValues()override;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;
	
	//Delegate����ϰ� Attribute �ٲ�� ��ε�ĳ��Ʈ�� �Ѹ���

protected:
	//Tag�� 
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAttributeInfo>pAttributeInfo = {};//��� ������ ���̺� �Ҵ��ҰŴ� 


};
