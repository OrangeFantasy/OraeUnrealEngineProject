#pragma once

#include "UObject/PrimaryAssetId.h"
#include "OraeTypes.generated.h"

class UOraeDataAsset;

USTRUCT(BlueprintType)
struct ORAEPROJECT_API FOraeAssetSlot
{
	GENERATED_USTRUCT_BODY()

	FOraeAssetSlot() : SlotNumber(-1) {}

	FOraeAssetSlot(int32 InSlotNumber, const FPrimaryAssetType& InAssetType) : SlotNumber(InSlotNumber), AssetType(InAssetType) {}

	bool IsValid() const { return SlotNumber >= 0 && AssetType.IsValid(); }

	friend inline uint32 GetTypeHash(const FOraeAssetSlot& Key)
	{
		uint32 Hash = 0;
		Hash = HashCombine(Hash, GetTypeHash(Key.AssetType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		return Hash;
	}

	bool operator==(const FOraeAssetSlot& Other) const { return SlotNumber == Other.SlotNumber && AssetType == Other.AssetType; }

	bool operator!=(const FOraeAssetSlot& Other) const { return !(*this == Other); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset")
	int32 SlotNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset")
	FPrimaryAssetType AssetType;
};