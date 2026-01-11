// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/UGEC/UGEC_FireballDamage.h"
#include "Ability/Attribute/EnemyAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExecutionCalculation.h"

struct FFireballgDamageStatics
{
	//Health 어트리뷰트를 캡처할거라고 정의
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	FFireballgDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, Health, Target, false);
	}
};

static FFireballgDamageStatics& FireballDamageStatics()
{
	static FFireballgDamageStatics Statics;
	return Statics;
}

UUGEC_FireballDamage::UUGEC_FireballDamage()
{
	RelevantAttributesToCapture.Add(FireballDamageStatics().HealthDef);

	Tag_DebuffBurn = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Burn"));
}

void UUGEC_FireballDamage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!TargetASC) return;

	float BaseDamage = Damage;

	if (TargetASC->HasMatchingGameplayTag(Tag_DebuffBurn))
	{
		BaseDamage *= Multiplier;
	}

	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(
			FireballDamageStatics().HealthProperty,
			EGameplayModOp::Additive,
			-BaseDamage));
}
