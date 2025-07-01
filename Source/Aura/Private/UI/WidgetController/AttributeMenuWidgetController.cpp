// copyright


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include"AbilitySystem/MH_AttributeSet.h"
#include"Data/AttributeInfo.h"
#include "Managers/TagManager.h"
void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//Super::BroadcastInitialValues();

	UMH_AttributeSet* AS = CastChecked<UMH_AttributeSet>(AttributeSet);

	check(pAttributeInfo);

	FAuraAttributeInfo Info =
		pAttributeInfo->
		FindAttributeInfoForTag(CTagManager::Get().GetTag(FName("Attributes.Primary.Strength")), false);

	Info.AttirbuteValue = AS->GetStrength();

	AttributeInfoDelegate.Broadcast(Info);

}
void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	//Super::BindCallbacksToDependencies();


	
}