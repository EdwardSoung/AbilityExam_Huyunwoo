// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Abilities/GameplayAbility_Fireball.h"
#include "Projectile/FireballProjectile.h"

UGameplayAbility_Fireball::UGameplayAbility_Fireball()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_Fireball::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	//생성
	SpawnProjectile();
	//생성만 해주고 효과는 Projectile이 들고있는다..

	//End
	//날아가니까 End처리를 음..
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGameplayAbility_Fireball::SpawnProjectile()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor) return;

	FTransform SpawnTransform(AvatarActor->GetActorRotation(), AvatarActor->GetActorLocation() + AvatarActor->GetActorForwardVector() * 100.0f);

	AFireballProjectile* Projectile = GetWorld()->SpawnActorDeferred<AFireballProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (Projectile)
	{
		Projectile->FinishSpawning(SpawnTransform);
	}
}
