// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include <InputAction.h>
#include "Ability/Attribute/PlayerAttributeSet.h"
//#include "Data/AbilityEnums.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ABILITYEXAM_HYUNWOO_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	}
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Skill(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UGameplayAbility> FireballAbilityClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> InitEffectClass = nullptr;
	UPROPERTY()
	TObjectPtr<UPlayerAttributeSet> PlayerAttributeSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> SkillAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> PlayerStatusWidgetClass = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	TObjectPtr<class UPlayerStatusWidget> PlayerStatusWidget = nullptr;
};
