// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "UGEC_FireballDamage.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYEXAM_HYUNWOO_API UUGEC_FireballDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	UUGEC_FireballDamage();

	virtual void Execute_Implementation
	(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CustomData")
	float Multiplier = 2.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CustomData")
	float Damage = 10.0f;
private:
	FGameplayTag Tag_DebuffBurn;
};
