// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Attribute/EnemyAttributeSet.h"
#include "GameplayEffectExtension.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	InitMaxHealth(100.0f);
	InitHealth(100.0f);
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//»ç¸Á?À½..
		//UE_LOG(LogTemp, Log, TEXT("Health Changed : %d"), GetHealth());
	}
}
