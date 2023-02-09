// Fill out your copyright notice in the Description page of Project Settings.

#include "Utils/OraeAssetManager.h"
#include "Utils/OraeDataAsset.h"

#include "AbilitySystemGlobals.h"

DEFINE_LOG_CATEGORY_STATIC(LogOraeAssetManager, All, All);

const FPrimaryAssetType UOraeAssetManager::PotionAssetType = TEXT("Potion");

const FPrimaryAssetType UOraeAssetManager::SkillAssetType = TEXT("Skill");

const FPrimaryAssetType UOraeAssetManager::TokenAssetType = TEXT("Token");

const FPrimaryAssetType UOraeAssetManager::WeaponAssetType = TEXT("Weapon");

UOraeAssetManager& UOraeAssetManager::Get()
{
	UOraeAssetManager* This = Cast<UOraeAssetManager>(GEngine->AssetManager);
	if (This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogOraeAssetManager, Fatal, TEXT("Invalid, AssetManager in DefaultEngine.ini. New Object<UOraeAssetManager>"));
		return *NewObject<UOraeAssetManager>();
	}
}

void UOraeAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}

