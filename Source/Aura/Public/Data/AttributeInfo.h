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

/*Editer에서 보여야 하는 Text 는 FText로 처리해야 한다. */
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
FText AttributeName = FText();

UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
FText AttributeDesc = FText();

/*이것은 영구적인것이라 노출하면 안될거*/
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

	/* text나 이런거는 거기서 채울거임editor */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> m_AttributeInfo;

	//표에서 이거 상속받은 데이터 어셋 만들어놨고 데이터 이미 채움-> 위젯컨트롤러에서 박아주면 사용가능
};
