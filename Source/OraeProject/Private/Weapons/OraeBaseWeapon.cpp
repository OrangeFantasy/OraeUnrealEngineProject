// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapons/OraeBaseWeapon.h"

AOraeBaseWeapon::AOraeBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void AOraeBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
