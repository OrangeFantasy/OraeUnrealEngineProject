// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "OraeAbilitySystemComponent.generated.h"

class UOraeGameplayAbility;

UCLASS()
class ORAEPROJECT_API UOraeAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void GetActiveAbilitiesWithTags(FGameplayTagContainer Tag, TArray<UOraeGameplayAbility*>& OutActiveAbilities);

	UFUNCTION(BlueprintCallable)
	UOraeAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool bLookForComponent);
};
