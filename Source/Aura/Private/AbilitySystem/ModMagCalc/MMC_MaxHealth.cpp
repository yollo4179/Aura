// copyright


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"
#include"AbilitySystem/MH_AttributeSet.h"
#include"Interact/CombatInterface.h"
UMMC_MaxHealth::UMMC_MaxHealth()
{



	VigorDef.AttributeToCapture = UMH_AttributeSet::GetVigorAttribute();

	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;



	VigorDef.bSnapshot = false;
	//SnapShot은 객체 생성되자마자 캡쳐// False로 하면 이펙트가 적용되는 순간만 캡쳐(Vigor가 세팅, 초기화될때마다)

	RelevantAttributesToCapture.Add(VigorDef);//캡쳐할 대상을 어레이에 등록해야한다. 

//modifier가 실행되고, 이펙트가 적용되면 타겟으로부터 캡쳐한 VigorDef으로의 접근을  보장받을수 있다. CalculateBaseMagnitude_Implementation->여기서 
}


float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//SorceTag랑 TargetTag 가져옴 설정한

	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvalParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

//Tag 는 넣든 말든 상관 없다. 

	float Vigor = {};
	GetCapturedAttributeMagnitude(VigorDef,Spec, EvalParams,Vigor);

	ICombatInterface*  pSourceCharacter =Cast<ICombatInterface> (Spec.GetContext().GetSourceObject());
	int32 Level= pSourceCharacter->GetCharacterLevel();

	return 80.f + Vigor*2.5f+   Level * 10.f;

}