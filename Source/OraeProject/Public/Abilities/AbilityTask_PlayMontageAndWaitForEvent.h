// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_PlayMontageAndWaitForEvent.generated.h"

class UOraeAbilitySystemComponent;

/** Delegate type used, EventTag and Payload may be empty if it came from the montage callbacks */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

UCLASS()
class ORAEPROJECT_API UAbilityTask_PlayMontageAndWaitForEvent : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAbilityTask_PlayMontageAndWaitForEvent(const FObjectInitializer& ObjectInitializer);

public:
	UFUNCTION(BlueprintCallable, Category = "Ability | Tasks",
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_PlayMontageAndWaitForEvent* PlayMontageAndWaitForEvent(UGameplayAbility* OwningAbility, //
		FName TaskInstanceName,																					//
		FGameplayTagContainer EventTag,																			//
		UAnimMontage* MontageToPlay,																			//
		float Rate = 1.0f,																						//
		FName StartSection = NAME_None,																			//
		bool bStopWhenAbilityEnds = true,																		//
		float AnimRootMotionTranslationScale = 1.0f,															//															//
		bool OnlyTriggerOnce = false,																			//
		bool OnlyMatchExact = true);

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate OnBlendOut;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate OnInterrupted;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate OnCancelled;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate EventReceived;

private:
	UOraeAbilitySystemComponent* GetTargetASC();

	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	virtual FString GetDebugString() const override;

	bool StopPlayingMontage();

	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnAbilityCancelled();
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle CancelledHandle;
	FDelegateHandle EventHandle;

private:
	UPROPERTY()
	TObjectPtr<UAnimMontage> MontageToPlay;

	UPROPERTY()
	FGameplayTagContainer EventTag;

	UPROPERTY()
	float Rate;

	UPROPERTY()
	FName StartSection;

	UPROPERTY()
	float AnimRootMotionTranslationScale;

	UPROPERTY()
	bool bStopWhenAbilityEnds;
};
