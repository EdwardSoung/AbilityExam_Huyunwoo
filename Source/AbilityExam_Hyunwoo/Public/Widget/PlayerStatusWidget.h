// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "PlayerStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYEXAM_HYUNWOO_API UPlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UStatusBarWidget> ManaBarWidget = nullptr;

	float MaxValue = 0.0f;
public:
	void OnCurrentChange(const FOnAttributeChangeData& InData);
	void OnMaxChange(const FOnAttributeChangeData& InData);
};
