// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OraeBaseWeapon.generated.h"

UCLASS()
class ORAEPROJECT_API AOraeBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AOraeBaseWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* WeaponMesh;

protected:
	virtual void BeginPlay() override;


};
