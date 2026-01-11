// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "StatusBarWidget.generated.h"

class UStatusProgressBarWidget;

/**
 * 
 */
UCLASS()
class ABILITYEXAM_HYUNWOO_API UStatusBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> Bar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CurrentValueText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> MaxValueText;
	
	float MaxValue = 0.0f;
public:
	void OnCurrentChange(const FOnAttributeChangeData& InData);
	void OnMaxChange(const FOnAttributeChangeData& InData);

	UFUNCTION(BlueprintCallable)
	void SetHealthColor(FLinearColor InColor);
	UFUNCTION(BlueprintCallable)
	void SetManaColor(FLinearColor InColor);
};
