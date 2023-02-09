// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "OraeAssetManager.generated.h"

UCLASS()
class ORAEPROJECT_API UOraeAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UOraeAssetManager() = default;

public:
	static const FPrimaryAssetType PotionAssetType;

	static const FPrimaryAssetType SkillAssetType;

	static const FPrimaryAssetType TokenAssetType;

	static const FPrimaryAssetType WeaponAssetType;

public:
	static UOraeAssetManager& Get();

	virtual void StartInitialLoading() override;
};
