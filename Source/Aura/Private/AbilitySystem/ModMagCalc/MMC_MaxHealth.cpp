// copyright


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"
#include"AbilitySystem/MH_AttributeSet.h"
#include"Interact/CombatInterface.h"
UMMC_MaxHealth::UMMC_MaxHealth()
{



	VigorDef.AttributeToCapture = UMH_AttributeSet::GetVigorAttribute();

	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;



	VigorDef.bSnapshot = false;
	//SnapShot�� ��ü �������ڸ��� ĸ��// False�� �ϸ� ����Ʈ�� ����Ǵ� ������ ĸ��(Vigor�� ����, �ʱ�ȭ�ɶ�����)

	RelevantAttributesToCapture.Add(VigorDef);//ĸ���� ����� ��̿� ����ؾ��Ѵ�. 

//modifier�� ����ǰ�, ����Ʈ�� ����Ǹ� Ÿ�����κ��� ĸ���� VigorDef������ ������  ��������� �ִ�. CalculateBaseMagnitude_Implementation->���⼭ 
}


float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//SorceTag�� TargetTag ������ ������

	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvalParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

//Tag �� �ֵ� ���� ��� ����. 

	float Vigor = {};
	GetCapturedAttributeMagnitude(VigorDef,Spec, EvalParams,Vigor);

	ICombatInterface*  pSourceCharacter =Cast<ICombatInterface> (Spec.GetContext().GetSourceObject());
	int32 Level= pSourceCharacter->GetCharacterLevel();

	return 80.f + Vigor*2.5f+   Level * 10.f;

}