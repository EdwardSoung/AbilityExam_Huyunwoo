// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Fireball.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYEXAM_HYUNWOO_API UGameplayAbility_Fireball : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbility_Fireball();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	void SpawnProjectile();
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Ability|Fireball")
	TSubclassOf<class AFireballProjectile> ProjectileClass = nullptr;
};
