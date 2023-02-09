// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "OraeGameplayAbility.generated.h"

//USTRUCT(BlueprintType)
//struct FOraeGameplayEffectContainerSpec
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	FOraeGameplayEffectContainerSpec() {}
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
//	FGameplayAbilityTargetDataHandle TargetData;
//
//	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
//	TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;
//
//	bool HasValidEffects() const { return TargetGameplayEffectSpecs.Num() > 0; }
//
//	bool HasValidTargets() const { return TargetData.Num() > 0; }
//
//	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors)
//	{
//		for (const FHitResult& HitResult : HitResults)
//		{
//			FGameplayAbilityTargetData_SingleTargetHit* NewData = new FGameplayAbilityTargetData_SingleTargetHit(HitResult);
//			TargetData.Add(NewData);
//		}
//
//		if (TargetActors.Num() > 0)
//		{
//			FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
//			NewData->TargetActorArray.Append(TargetActors);
//			TargetData.Add(NewData);
//		}
//	}
//};

UCLASS()
class ORAEPROJECT_API UOraeGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UOraeGameplayAbility();

//public:
//	/** Make gameplay effect container spec to be applied later, using the passed in container */
//	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
//	FOraeGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(
//		const FGameplayTagContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
//
//	/** Search for and make a gameplay effect container spec to be applied later, from the EffectContainerMap */
//	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
//	FOraeGameplayEffectContainerSpec MakeEffectContainerSpec(
//		FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
//
//	/** Applies a gameplay effect container spec that was previously created */
//	UFUNCTION(BlueprintCallable, Category = Ability)
//	TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FOraeGameplayEffectContainerSpec& ContainerSpec);
//
//	/** Applies a gameplay effect container, by creating and then applying the spec */
//	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
//	TArray<FActiveGameplayEffectHandle> ApplyEffectContainer(
//		FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
//
//public:
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
//	TMap<FGameplayTag, FGameplayTagContainer> EffectContainerMap;
};
