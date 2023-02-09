// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/OraeBaseCharacter.h"
#include "Components/OraeWeaponComponent.h"
#include "Abilities/OraeGameplayAbility.h"
#include "Abilities/OraeAttributeSet.h"
#include "Abilities/OraeAbilitySystemComponent.h"
#include "UI/OraeCharacterAttributeWidget.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

AOraeBaseCharacter::AOraeBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	if (SpringArmComponent)
	{
		SpringArmComponent->SetupAttachment(GetRootComponent());
		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->TargetArmLength = 400.0f;
		SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);
	}

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	if (CameraComponent)
	{
		CameraComponent->SetupAttachment(SpringArmComponent);
	}

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	if (WidgetComponent)
	{
		WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		WidgetComponent->SetWidgetClass(UOraeCharacterAttributeWidget::StaticClass());
		WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	WeaponComponent = CreateDefaultSubobject<UOraeWeaponComponent>(TEXT("WeaponComponent"));

	AbilitySystemComponent = CreateDefaultSubobject<UOraeAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetIsReplicated(true);
		AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	}

	AttributeSet = CreateDefaultSubobject<UOraeAttributeSet>(TEXT("AttributeSet"));
	if (AttributeSet)
	{
		AttributeSet->OnHealthChanged.AddUObject(this, &AOraeBaseCharacter::OnHealthChanged);
	}
}

void AOraeBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(MovementMappingContext, 0);
			Subsystem->AddMappingContext(AbilitiesMappingContext, 0);
		}
	}

	InitCharacterUI();
}

void AOraeBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOraeBaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AOraeBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOraeBaseCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOraeBaseCharacter::Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AOraeBaseCharacter::Run);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AOraeBaseCharacter::StopRunning);
	}
}

void AOraeBaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	// bIsMovingForward = MovementVector.Y > 0;

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AOraeBaseCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AOraeBaseCharacter::Run()
{
	if (!bIsRunning && GetCharacterMovement())
	{
		bIsRunning = true;
		GetCharacterMovement()->MaxWalkSpeed *= RunningModify;
	}
}

void AOraeBaseCharacter::StopRunning()
{
	if (bIsRunning && GetCharacterMovement())
	{
		bIsRunning = false;
		GetCharacterMovement()->MaxWalkSpeed /= RunningModify;
	}
}

float AOraeBaseCharacter::GetMovementDirection() const
{
	if (!GetVelocity().IsZero())
	{
		const FVector VelocityNormal = GetVelocity().GetSafeNormal();

		const double AngleBetween = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal)));
		const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

		return CrossProduct.IsZero() ? AngleBetween : AngleBetween * FMath::Sign(CrossProduct.Z);
	}
	return 0.0f;
}

bool AOraeBaseCharacter::IsRunning() const
{
	return bIsRunning;
}

bool AOraeBaseCharacter::IsAlive() const
{
	return !FMath::IsNearlyZero(AttributeSet->GetHealth());
}

//float AOraeBaseCharacter::GetHealth() const
//{
//	return AttributeSet->GetHealth();
//}
//
//float AOraeBaseCharacter::GetMaxHealth() const
//{
//	return AttributeSet->GetMaxHealth();
//}

void AOraeBaseCharacter::OnHealthChanged()
{
	if (!IsAlive())
	{
		Death();
	}

	if (WidgetComponent && WidgetComponent->GetUserWidgetObject())
	{
		UOraeCharacterAttributeWidget* AttributeWidget = Cast<UOraeCharacterAttributeWidget>(WidgetComponent->GetUserWidgetObject());
		if (AttributeWidget)
		{
			AttributeWidget->SetHealth(AttributeSet->GetHealth());
		}
	}
}

void AOraeBaseCharacter::Death()
{
	// WeaponComponent->StopFire();

	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetLifeSpan(LifeSpanOnDeath);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

	if (bSimulatePhysics)
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetMesh()->SetSimulatePhysics(bSimulatePhysics);
	}
	else
	{
		GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
		PlayAnimMontage(DeathAnimMontage);
	}
}

void AOraeBaseCharacter::InitCharacterUI()
{
	if (WidgetComponent)
	{
		UOraeCharacterAttributeWidget* AttributeWidget = Cast<UOraeCharacterAttributeWidget>(WidgetComponent->GetUserWidgetObject());
		if (AttributeWidget)
		{
			AttributeWidget->SetHealth(AttributeSet->GetHealth());
			AttributeWidget->SetMaxHealth(AttributeSet->GetMaxHealth());
			AttributeWidget->SetMana(AttributeSet->GetMana());
			AttributeWidget->SetMaxMana(AttributeSet->GetMana());
		}
	}
}

// ****************************************
// *        GameplayAbilitySystem         *
// ****************************************

UAbilitySystemComponent* AOraeBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AOraeBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}

void AOraeBaseCharacter::AddStartupGameplayAbilities()
{
	if (GetLocalRole() == ROLE_Authority && !bAbilitiesInitialized)
	{
		for (TSubclassOf<UOraeGameplayAbility>& StartUpAbility : GameplayAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartUpAbility, //
				CharacterLevel,														 //
				INDEX_NONE, // static_cast<int32>(StartUpAbility.GetDefaultObject()->AbilityInputID), //
				this));
		}

		for (TSubclassOf<UGameplayEffect>& Effect : GameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, CharacterLevel, EffectContext);
			if (NewHandle.IsValid())
			{
				// FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
				AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
			}
		}

		bAbilitiesInitialized = true;
	}
}

// void AOraeBaseCharacter::AddSlottedGameplayAbilities()
//{
//	TMap<FOraeAssetSlot, FGameplayAbilitySpec> SlottedAbilitySpecs;
//	FillSlottedAbilitySpecs(SlottedAbilitySpecs);
//
//	for (const TPair<FOraeAssetSlot, FGameplayAbilitySpec>& SpecPair : SlottedAbilitySpecs)
//	{
//		FGameplayAbilitySpecHandle& SpecHandle = CurrentSlottedAbilities.FindOrAdd(SpecPair.Key);
//		if (!SpecHandle.IsValid())
//		{
//			SpecHandle = AbilitySystemComponent->GiveAbility(SpecPair.Value);
//		}
//	}
// }

// void AOraeBaseCharacter::FillSlottedAbilitySpecs(TMap<FOraeAssetSlot, FGameplayAbilitySpec>& OutSlottedAbilitySpecs)
//{
//	// Add Defaults Abilities.
//	// ...
//
//	if (InventorySource)
//	{
//		const TMap<FOraeAssetSlot, UOraeDataAsset*>& SkottedAssetMap = InventorySource->GetSlottedAssetMap();
//		for (const TPair<FOraeAssetSlot, UOraeDataAsset*>& AssetPair : SkottedAssetMap)
//		{
//			UOraeDataAsset* SlottedAsset = AssetPair.Value;
//
//			int32 AbilityLevel = GetCharacterLevel();
//			if (SlottedAsset && SlottedAsset->AssetType.GetName() == FName(TEXT("Weapon")))
//			{
//				AbilityLevel = SlottedAsset->AbilityLevel;
//			}
//
//			if (SlottedAsset && SlottedAsset->GrantedAbility)
//			{
//				OutSlottedAbilitySpecs.Add(
//					AssetPair.Key, FGameplayAbilitySpec(SlottedAsset->GrantedAbility, AbilityLevel, INDEX_NONE, SlottedAsset));
//			}
//		}
//	}
// }

int32 AOraeBaseCharacter::GetCharacterLevel() const
{
	return CharacterLevel;
}

// void AOraeBaseCharacter::HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
//{
//	if (bAbilitiesInitialized)
//	{
//		OnHealthChanged(DeltaValue, EventTags);
//	}
// }
//
// void AOraeBaseCharacter::HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
//{
//	if (bAbilitiesInitialized)
//	{
//		OnManaChanged(DeltaValue, EventTags);
//	}
// }
//
// void AOraeBaseCharacter::HandleDamage(float DamageAmount, const FHitResult& HitInfo, //
//	const FGameplayTagContainer& DamageTags, AOraeBaseCharacter* InstigatorPawn, AActor* DamageCauser)
//{
//	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorPawn, DamageCauser);
// }
//

bool AOraeBaseCharacter::IsUsingAbilityWith(FGameplayTagContainer Tag) const
{
	TArray<UOraeGameplayAbility*> ActiveAbilities;
	AbilitySystemComponent->GetActiveAbilitiesWithTags(Tag, ActiveAbilities);

	return ActiveAbilities.Num() > 0;
}
