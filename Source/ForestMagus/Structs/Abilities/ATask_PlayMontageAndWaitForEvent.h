// Fill out your copyright notice in the Description page of Project Settings.
// 
//@CopyRight Winter
//Action RPG에서 가져온 코드
//웬만해서는 건드리지말것


#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ATask_PlayMontageAndWaitForEvent.generated.h"


class UFMAbilitySystemComponent;

/** Delegate type used, EventTag and Payload may be empty if it came from the montage callbacks */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSGPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UATask_PlayMontageAndWaitForEvent : public UAbilityTask
{
	GENERATED_BODY()
public:
	UATask_PlayMontageAndWaitForEvent(const FObjectInitializer& ObjectInitializer);

	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;

	/** The montage completely finished playing */
	UPROPERTY(BlueprintAssignable)
		FSGPlayMontageAndWaitForEventDelegate OnCompleted;

	/** The montage started blending out */
	UPROPERTY(BlueprintAssignable)
		FSGPlayMontageAndWaitForEventDelegate OnBlendOut;

	/** The montage was interrupted */
	UPROPERTY(BlueprintAssignable)
		FSGPlayMontageAndWaitForEventDelegate OnInterrupted;

	/** The ability task was explicitly cancelled by another ability */
	UPROPERTY(BlueprintAssignable)
		FSGPlayMontageAndWaitForEventDelegate OnCancelled;

	/** One of the triggering gameplay events happened */
	UPROPERTY(BlueprintAssignable)
		FSGPlayMontageAndWaitForEventDelegate EventReceived;

	/**
	 * Play a montage and wait for it end. If a gameplay event happens that matches EventTags (or EventTags is empty), the EventReceived delegate will fire with a tag and event data.
	 * If StopWhenAbilityEnds is true, this montage will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled.
	 * On normal execution, OnBlendOut is called when the montage is blending out, and OnCompleted when it is completely done playing
	 * OnInterrupted is called if another montage overwrites this, and OnCancelled is called if the ability or task is cancelled
	 *
	 * @param TaskInstanceName Set to override the name of this task, for later querying
	 * @param MontageToPlay The montage to play on the character
	 * @param EventTags Any gameplay events matching this tag will activate the EventReceived callback. If empty, all events will trigger callback
	 * @param Rate Change to play the montage faster or slower
	 * @param bStopWhenAbilityEnds If true, this montage will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled
	 * @param AnimRootMotionTranslationScale Change to modify size of root motion or set to 0 to block it entirely
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UATask_PlayMontageAndWaitForEvent* PlayMontageAndWaitForEvent(
			UGameplayAbility* OwningAbility,
			FName TaskInstanceName,
			UAnimMontage* MontageToPlay,
			FGameplayTagContainer EventTags,
			float Rate = 1.f,
			FName StartSection = NAME_None,
			bool bStopWhenAbilityEnds = true,
			float AnimRootMotionTranslationScale = 1.f);
private:
	/** Montage that is playing */
	UPROPERTY()
		UAnimMontage* MontageToPlay;

	/** List of tags to match against gameplay events */
	UPROPERTY()
		FGameplayTagContainer EventTags;

	/** Playback rate */
	UPROPERTY()
		float Rate;

	/** Section to start montage from */
	UPROPERTY()
		FName StartSection;

	/** Modifies how root motion movement to apply */
	UPROPERTY()
		float AnimRootMotionTranslationScale;

	/** Rather montage should be aborted if ability ends */
	UPROPERTY()
		bool bStopWhenAbilityEnds;

	/** Checks if the ability is playing a montage and stops that montage, returns true if a montage was stopped, false if not. */
	bool StopPlayingMontage();

	/** Returns our ability system component */
	UFMAbilitySystemComponent* GetTargetASC();

	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	void OnAbilityCancelled();
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle CancelledHandle;
	FDelegateHandle EventHandle;
};
