// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OraeWeaponComponent.generated.h"

class AOraeBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ORAEPROJECT_API UOraeWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOraeWeaponComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AOraeBaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<AOraeBaseWeapon> CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WeaponSocketName = "WeaponSocket";

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:
	void LoadWeapon();
};
