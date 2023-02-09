// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "OraeBaseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UOraeWeaponComponent;
class UOraeAbilitySystemComponent;
class UOraeGameplayAbility;
class UOraeAttributeSet;
class UGameplayEffect;
class UWidgetComponent;
class UOraeCharacterAttributeWidget;

struct FInputActionValue;

UCLASS()
class ORAEPROJECT_API AOraeBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AOraeBaseCharacter();

	// *********************************************
	// *         Character Basic Setting           *
	// *********************************************

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Attribute")
	bool IsAlive() const;

	//UFUNCTION(BlueprintCallable, Category = "Attribute")
	//float GetHealth() const;

	//UFUNCTION(BlueprintCallable, Category = "Attribute")
	//float GetMaxHealth() const;

protected:
	virtual void BeginPlay() override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnHealthChanged();

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Run();
	void StopRunning();

	void Death();

	void InitCharacterUI();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UOraeWeaponComponent> WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UOraeAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> MovementMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> AbilitiesMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RunningModify = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool bSimulatePhysics = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	TObjectPtr<UAnimMontage> DeathAnimMontage;

private:
	bool bIsMovingForward = false;

	bool bIsRunning = false;

	// *********************************************
	// *          Gameplay Ability System          *
	// *********************************************

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable)
	int32 GetCharacterLevel() const;

protected:
	// UFUNCTION(BlueprintImplementableEvent)
	// void OnHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags);

	// UFUNCTION(BlueprintImplementableEvent)
	// void OnManaChanged(float DeltaValue, const FGameplayTagContainer& EventTags);

	// UFUNCTION(BlueprintImplementableEvent)
	// void OnDamaged(float DamageAmount, const FHitResult& HitInfo, //
	//	const FGameplayTagContainer& DamageTags, AOraeBaseCharacter* InstigatorCharacter, AActor* DamageCauser);

private:
	void AddStartupGameplayAbilities();
	// void AddSlottedGameplayAbilities();
	// void FillSlottedAbilitySpecs(TMap<FOraeAssetSlot, FGameplayAbilitySpec>& OutSlottedAbilitySpecs);

	// void HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags);
	// void HandleManaChanged(float DeltaValue, const FGameplayTagContainer& EventTags);
	// void HandleDamage(float DamageAmount, const FHitResult& HitInfo, //
	//	const FGameplayTagContainer& DamageTags, AOraeBaseCharacter* InstigatorCharacter, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	bool IsUsingAbilityWith(FGameplayTagContainer Tag) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UOraeGameplayAbility>> GameplayAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	UPROPERTY()
	TObjectPtr<UOraeAttributeSet> AttributeSet;

	UPROPERTY()
	bool bAbilitiesInitialized = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharacterLevel = 1;

private:
	friend UOraeAttributeSet;
};

// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
// TMap<FOraeAssetSlot, TSubclassOf<UOraeGameplayAbility>> DefaultSlottedAbilities;
//
// UPROPERTY()
// TScriptInterface<IOraeInventoryInterface> InventorySource;

// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// TMap<FOraeAssetSlot, FGameplayAbilitySpecHandle> CurrentSlottedAbilities;
