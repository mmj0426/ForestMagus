// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ForestMagus.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Structs/Abilities/FMAbilityTypes.h"
#include "FMTargetType.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UFMTargetType : public UObject
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	UFMTargetType() {}

	/** Called to determine targets to apply gameplay effects to */
	UFUNCTION(BlueprintNativeEvent)
	void GetTargets(ABaseCharacter* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};
