// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Data/AbilityEnums.h"
#include "Widget/PlayerStatusWidget.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("Player Attribute"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		if (PlayerStatusWidgetClass)
		{
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			PlayerStatusWidget = CreateWidget<UPlayerStatusWidget>(PlayerController, PlayerStatusWidgetClass);
			if (PlayerStatusWidget)
			{
				PlayerStatusWidget->AddToViewport();

				FOnGameplayAttributeValueChange& OnHealthChanged =
					AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute());

				OnHealthChanged.AddUObject(PlayerStatusWidget, &UPlayerStatusWidget::OnCurrentChange);

				FOnGameplayAttributeValueChange& OnMaxHealthChanged =
					AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxManaAttribute());

				OnMaxHealthChanged.AddUObject(PlayerStatusWidget, &UPlayerStatusWidget::OnMaxChange);
			}
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

		if (FireballAbilityClass)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(
					FireballAbilityClass,
					1,
					static_cast<int32>(EAbilityInputID::Fireball),
					this)
			);
		}
	}
}

void APlayerCharacter::Skill(const FInputActionValue& Value)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::Fireball));
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		if (SkillAction)
			EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Started, this, &APlayerCharacter::Skill);
	}
}

