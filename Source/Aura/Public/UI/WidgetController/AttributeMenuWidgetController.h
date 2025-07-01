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
	
	//Delegate등록하고 Attribute 바뀌면 브로드캐스트로 뿌린다

protected:
	//Tag를 
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAttributeInfo>pAttributeInfo = {};//어셋 데이터 테이블 할당할거다 


};
