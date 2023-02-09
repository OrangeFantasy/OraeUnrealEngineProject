// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OraeInventoryInterface.generated.h"

class UOraeDataAsset;
struct FOraeAssetSlot;

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UOraeInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

class ORAEPROJECT_API IOraeInventoryInterface
{
	GENERATED_BODY()

public:
	virtual const TMap<FOraeAssetSlot, UOraeDataAsset*>& GetSlottedAssetMap() const = 0;
};