// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/OraeWeaponComponent.h"
#include "Weapons/OraeBaseWeapon.h"

#include "GameFramework/Character.h"

UOraeWeaponComponent::UOraeWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UOraeWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadWeapon();
}

void UOraeWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentWeapon->Destroy();

	Super::EndPlay(EndPlayReason);
}

void UOraeWeaponComponent::LoadWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (Character && GetWorld())
	{
		CurrentWeapon = GetWorld()->SpawnActor<AOraeBaseWeapon>(WeaponClass);
		if (CurrentWeapon)
		{
			CurrentWeapon->SetOwner(Character);

			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponSocketName);
		}
	}
}
