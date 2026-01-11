// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GCN_FireballExplosion.h"
#include "NiagaraFunctionLibrary.h"
#include "GameplayEffectTypes.h"

UGCN_FireballExplosion::UGCN_FireballExplosion()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Ability.Fireball.Explosion"));
}

bool UGCN_FireballExplosion::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	FVector SpawnLocation = (MyTarget ? MyTarget->GetActorLocation() : FVector::ZeroVector);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	// 2. HitResult가 포함되어 있는지 확인 (파이어볼에서 AddHitResult 한 것)
	if (Parameters.EffectContext.IsValid())
	{
		const FHitResult* Hit = Parameters.EffectContext.GetHitResult();
		if (Hit)
		{
			SpawnLocation = Hit->Location; // 혹은 Hit->ImpactPoint
			// 표면의 법선 벡터(Normal)를 기준으로 회전값을 구함 (벽에 맞으면 벽 방향으로 터지게)
			SpawnRotation = Hit->ImpactNormal.Rotation();
		}

		UWorld* World = GetWorld();
		if (World)
		{
			// 3. 파티클 재생
			if (ExplosionFX)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(
					this,                 // WorldContextObject
					ExplosionFX,         // 스폰할 나이아가라 시스템 에셋
					Hit->ImpactPoint,      // 위치
					Hit->ImpactNormal.Rotation() // 회전 (충돌 면의 법선 방향)
				);
			}
		}
	}

	return true;
}
