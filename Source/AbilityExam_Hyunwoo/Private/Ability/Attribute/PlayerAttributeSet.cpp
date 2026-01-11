// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Attribute/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitMaxMana(200.0f);
	InitMana(200.0f);
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

}
