// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStatusWidget.h"
#include "StatusBarWidget.h"

void UPlayerStatusWidget::OnCurrentChange(const FOnAttributeChangeData& InData)
{
	if (ManaBarWidget)
	{
		ManaBarWidget->OnCurrentChange(InData);
	}
}
void UPlayerStatusWidget::OnMaxChange(const FOnAttributeChangeData& InData)
{
	if (ManaBarWidget)
	{
		ManaBarWidget->OnMaxChange(InData);
	}
}