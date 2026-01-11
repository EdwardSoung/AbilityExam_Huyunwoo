// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/FireballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Ability/Attribute/EnemyAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AFireballProjectile::AFireballProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AFireballProjectile::OnOverlapBegin);
    SetRootComponent(SphereCollision);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

    InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void AFireballProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireballProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireballProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == GetOwner())
        return;

    // 상대방의 ASC 가져오기
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
    UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetInstigator());
    if (TargetASC && SourceASC)
    {
        FGameplayEffectContextHandle FireballContext = TargetASC->MakeEffectContext();

        FGameplayEffectContextHandle ContextHandle = SourceASC->MakeEffectContext();
        
        FGameplayEffectSpecHandle DamageSpecHandle =
            SourceASC->MakeOutgoingSpec(DamageEffectClass, 1.0f, ContextHandle);

        ContextHandle.AddHitResult(SweepResult);

        //맞으면 데미지
        if (DamageSpecHandle.IsValid())
        {
            SourceASC->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), TargetASC);
        }

        //그냥 시간동안 화상 상태로
        FGameplayEffectSpecHandle BurnSpecHandle = 
            SourceASC->MakeOutgoingSpec(BurnEffectClass, 1.0f, ContextHandle);
        if (BurnSpecHandle.IsValid())
        {
            SourceASC->ApplyGameplayEffectSpecToTarget(*BurnSpecHandle.Data.Get(), TargetASC);
        }

    }

    Destroy();
}

