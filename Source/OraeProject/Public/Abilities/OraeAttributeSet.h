// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "OraeAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)                                                                                       \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)                                                                             \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)                                                                                           \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)                                                                                           \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_MULTICAST_DELEGATE(FOnAttributeEvent);

UCLASS()
class ORAEPROJECT_API UOraeAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UOraeAttributeSet();

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UOraeAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UOraeAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UOraeAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UOraeAttributeSet, MaxMana)

	//UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Damage, Category = "Damage")
	//FGameplayAttributeData Damage;
	//ATTRIBUTE_ACCESSORS(UOraeAttributeSet, Damage)

	FOnAttributeEvent OnHealthChanged;
	FOnAttributeEvent OnManaChanged;

public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	//UFUNCTION()
	//void OnRep_Damage(const FGameplayAttributeData& OldValue);

private:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute,
		float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
