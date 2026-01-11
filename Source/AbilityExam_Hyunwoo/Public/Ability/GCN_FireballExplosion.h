// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GCN_FireballExplosion.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class ABILITYEXAM_HYUNWOO_API UGCN_FireballExplosion : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
public:
	UGCN_FireballExplosion();

	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionFX;
};
