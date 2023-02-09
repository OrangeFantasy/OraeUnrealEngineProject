// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OraeCharacterAttributeWidget.generated.h"

UCLASS()
class ORAEPROJECT_API UOraeCharacterAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealth(float Value) { Health = Value; }
	void SetMaxHealth(float Value) { MaxHealth = Value; }
	void SetMana(float Value) { Mana = Value; }
	void SetMaxMana(float Value) { MaxMana = Value; }

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const { return MaxHealth == 0.0f ? 0.0f : Health / MaxHealth; }

	UFUNCTION(BlueprintCallable)
	float GetManaPercent() const { return MaxMana == 0.0f ? 0.0f : Mana / MaxMana; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	float Health;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	float Mana;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	float MaxMana;
};
