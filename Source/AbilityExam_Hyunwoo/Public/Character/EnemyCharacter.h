// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Data/AbilityEnums.h"
#include "Ability/Attribute/EnemyAttributeSet.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ABILITYEXAM_HYUNWOO_API AEnemyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	}

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UEnemyAttributeSet> EnemyAttributeSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> InitEffectClass = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<class UWidgetComponent> HealthBarWidget = nullptr;
};
