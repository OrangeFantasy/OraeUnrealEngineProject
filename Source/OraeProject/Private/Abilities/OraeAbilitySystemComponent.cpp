// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/OraeAbilitySystemComponent.h"
#include "Abilities/OraeGameplayAbility.h"

#include "AbilitySystemGlobals.h"

void UOraeAbilitySystemComponent::GetActiveAbilitiesWithTags(FGameplayTagContainer Tag, TArray<UOraeGameplayAbility*>& OutActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> ActivatableAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag, ActivatableAbilitySpecs, false);

	for (FGameplayAbilitySpec* AbilitySpec : ActivatableAbilitySpecs)
	{
		TArray<UGameplayAbility*> AbilityInstance = AbilitySpec->GetAbilityInstances();

		for (UGameplayAbility* AcitveAbility : AbilityInstance)
		{
			OutActiveAbilities.Add(Cast<UOraeGameplayAbility>(AcitveAbility));
		}
	}
}

UOraeAbilitySystemComponent* UOraeAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool bLookForComponent)
{
	return Cast<UOraeAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, bLookForComponent));
}
