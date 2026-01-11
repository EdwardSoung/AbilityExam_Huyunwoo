// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "FireballProjectile.generated.h"

UCLASS()
class ABILITYEXAM_HYUNWOO_API AFireballProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireballProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
public:
	UPROPERTY(EditAnywhere, Category = "Projectile")
	TObjectPtr<class USphereComponent> SphereCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile|Movement")
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovementComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<class UGameplayEffect> DamageEffectClass = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<class UGameplayEffect> BurnEffectClass = nullptr;
};
