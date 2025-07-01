// copyright

#pragma once

#include"GameplayTagContainer.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"


USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY();

UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
FGameplayTag AttributeTag = FGameplayTag();

/*Editer���� ������ �ϴ� Text �� FText�� ó���ؾ� �Ѵ�. */
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
FText AttributeName = FText();

UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
FText AttributeDesc = FText();

/*�̰��� �������ΰ��̶� �����ϸ� �ȵɰ�*/
UPROPERTY(BlueprintReadOnly)
float AttirbuteValue= 0.f;



};

/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfo: public UDataAsset
{
	GENERATED_BODY()
public:
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag& GameplayTag, bool bLogNotFound = false)const ;

	/* text�� �̷��Ŵ� �ű⼭ ä�����editor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> m_AttributeInfo;

	//ǥ���� �̰� ��ӹ��� ������ ��� �������� ������ �̹� ä��-> ������Ʈ�ѷ����� �ھ��ָ� ��밡��
};
