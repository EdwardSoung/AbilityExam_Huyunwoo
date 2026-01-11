// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"
#include "Components/WidgetComponent.h"
#include "StatusBarWidget.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("Enemy Attribute"));

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		if (HealthBarWidget)
		{
			auto StatusWidget = Cast<UStatusBarWidget>(HealthBarWidget->GetUserWidgetObject());

			FOnGameplayAttributeValueChange& OnHealthChanged =
				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetHealthAttribute());

			OnHealthChanged.AddUObject(StatusWidget, &UStatusBarWidget::OnCurrentChange);

			FOnGameplayAttributeValueChange& OnMaxHealthChanged =
				AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetMaxHealthAttribute());

			OnMaxHealthChanged.AddUObject(StatusWidget, &UStatusBarWidget::OnMaxChange);
		}

		if (InitEffectClass)
		{
			FGameplayEffectContextHandle InitializeContext = AbilitySystemComponent->MakeEffectContext();
			FGameplayEffectSpecHandle InitializeSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InitEffectClass, 0, InitializeContext);
			if (InitializeSpecHandle.IsValid())
			{
				AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*InitializeSpecHandle.Data.Get());
			}
		}
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

