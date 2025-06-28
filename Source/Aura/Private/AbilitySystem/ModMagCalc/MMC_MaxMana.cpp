// copyright


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include"AbilitySystem/MH_AttributeSet.h"
#include"Interact/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	ManaDef.AttributeToCapture = UMH_AttributeSet::GetIntelligenceAttribute();
	ManaDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ManaDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(ManaDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec)const 
{
	/*To do*/
	/*1 Get Level */
	/*2 Get Inteligence Magnitude Changed*/
	FAggregatorEvaluateParameters EvalParams = {};
	EvalParams.SourceTags =  Spec.CapturedSourceTags.GetAggregatedTags();
	EvalParams.TargetTags =  Spec.CapturedTargetTags.GetAggregatedTags();

	float Intel = 0;
	GetCapturedAttributeMagnitude(ManaDef, Spec, EvalParams, Intel);

	ICombatInterface* pCharacter = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());

	int32 Level  = pCharacter->GetCharacterLevel();
	return  50.f+ 2.0f*Intel + 10 *Level;
}