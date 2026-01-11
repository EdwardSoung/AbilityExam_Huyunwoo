// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORIS(ClassName, PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ABILITYEXAM_HYUNWOO_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UEnemyAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
public:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Enemy")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORIS(UEnemyAttributeSet, Health)

		UPROPERTY(BlueprintReadOnly, Category = "Attribute|Enemy")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORIS(UEnemyAttributeSet, MaxHealth)
};
