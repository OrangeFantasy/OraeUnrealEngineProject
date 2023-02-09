// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/OraeAttributeSet.h"
#include "Abilities/OraeAbilitySystemComponent.h"

#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UOraeAttributeSet::UOraeAttributeSet() : Health(1.0f), MaxHealth(1.0f), Mana(0.0f), MaxMana(0.0f) {} //, Damage(0.0f) {}

void UOraeAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UOraeAttributeSet, Health);
	DOREPLIFETIME(UOraeAttributeSet, MaxHealth);
	DOREPLIFETIME(UOraeAttributeSet, Mana);
	DOREPLIFETIME(UOraeAttributeSet, MaxMana);
	// DOREPLIFETIME(UOraeAttributeSet, Damage);
}

void UOraeAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustAttributeForMaxChange(Mana, MaxMana, NewValue, GetManaAttribute());
	}
}

void UOraeAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// Compute the delta between old and new, if it is available.
	float DeltaValue = 0.0f;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	AActor* TargetActor = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		if (TargetActor)
		{
			OnHealthChanged.Broadcast();
		}
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
		if (TargetActor)
		{
			OnManaChanged.Broadcast();
		}
	}

	// if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	//{
	//	FHitResult HitResult;
	//	if (EffectContextHandle.GetHitResult())
	//	{
	//		HitResult = *EffectContextHandle.GetHitResult();
	//	}

	//	const float LocalDamageDone = GetDamage();
	//	SetDamage(0.0f);

	//	if (LocalDamageDone > 0)
	//	{
	//		const float OldHealth = GetHealth();
	//		SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));

	//	}
	//}
	/*
	// Get the Target actor, which should be our owner
	AOraeBaseCharacter* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetCharacter = Cast<AOraeBaseCharacter>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// Get the Source Actor.
		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		AOraeBaseCharacter* SourceCharacter = nullptr;
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();
			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(SourceActor))
				{
					SourceController = Pawn->GetController();
				}
			}

			// Use the controller to find the source pawn
			SourceCharacter = (SourceController											   //
								   ? Cast<AOraeBaseCharacter>(SourceController->GetPawn()) //
								   : Cast<AOraeBaseCharacter>(SourceActor));

			// Set the causer actor based on context if it's set
			if (EffectContextHandle.GetEffectCauser())
			{
				SourceActor = EffectContextHandle.GetEffectCauser();
			}
		}

		// Try to extract a hit result
		FHitResult HitResult;
		if (EffectContextHandle.GetHitResult())
		{
			HitResult = *EffectContextHandle.GetHitResult();
		}

		// Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalDamageDone = GetDamage();
		SetDamage(0.f);

		if (LocalDamageDone > 0)
		{
			// Apply the health change and then clamp it
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));

			if (TargetCharacter)
			{
				// This is proper damage
				TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);

				// Call for all health changes
				TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
			}
		}
	}
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		OnHealthChanged.Broadcast();
		 if (TargetCharacter)
		{
			TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
		 }
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
		OnManaChanged.Broadcast();
		 if (TargetCharacter)
		{
			TargetCharacter->HandleManaChanged(DeltaValue, SourceTags);
		 }
	}
	*/
}

void UOraeAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, //
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilitySystemComponent)
	{
		// Change current value to maintain the current Val / Max percent.
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.0f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilitySystemComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UOraeAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOraeAttributeSet, Health, OldValue);
}

void UOraeAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOraeAttributeSet, MaxHealth, OldValue);
}

void UOraeAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOraeAttributeSet, Mana, OldValue);
}

void UOraeAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOraeAttributeSet, MaxMana, OldValue);
}

// void UOraeAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldValue)
//{
//	GAMEPLAYATTRIBUTE_REPNOTIFY(UOraeAttributeSet, Damage, OldValue);
// }