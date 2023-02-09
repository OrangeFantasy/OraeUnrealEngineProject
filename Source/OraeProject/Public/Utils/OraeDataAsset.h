// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OraeDataAsset.generated.h"

class UOraeGameplayAbility;

UCLASS()
class ORAEPROJECT_API UOraeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UOraeDataAsset();

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	UFUNCTION(BlueprintCallable, Category = "DataAsset")
	FString GetIdentifierString() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Limit")
	bool IsConsumable() const;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataAsset")
	FPrimaryAssetType AssetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	FName AssetName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	FText AssetDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset")
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Limit")
	int32 MaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Limit")
	int32 MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<UOraeGameplayAbility> GrantedAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	int32 AbilityLevel;
};
