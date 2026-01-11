// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusBarWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UStatusBarWidget::OnCurrentChange(const FOnAttributeChangeData& InData)
{
	if(CurrentValueText)
		CurrentValueText->SetText(FText::AsNumber(InData.NewValue));

	if(Bar)
		Bar->SetPercent(InData.NewValue / MaxValue);
}

void UStatusBarWidget::OnMaxChange(const FOnAttributeChangeData& InData)
{
	MaxValue = InData.NewValue;
	if(MaxValueText)
		MaxValueText->SetText(FText::AsNumber(MaxValue));	
}

void UStatusBarWidget::SetHealthColor(FLinearColor InColor)
{
}

void UStatusBarWidget::SetManaColor(FLinearColor InColor)
{
}
