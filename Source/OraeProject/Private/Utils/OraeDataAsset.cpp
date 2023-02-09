// Fill out your copyright notice in the Description page of Project Settings.

#include "Utils/OraeDataAsset.h"
#include "Utils/OraeTypes.h"

UOraeDataAsset::UOraeDataAsset() : Price(0), MaxCount(1), MaxLevel(1), AbilityLevel(1) {}

FPrimaryAssetId UOraeDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(AssetType, GetFName());
}

FString UOraeDataAsset::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

bool UOraeDataAsset::IsConsumable() const
{
	return MaxCount <= 0;
}
