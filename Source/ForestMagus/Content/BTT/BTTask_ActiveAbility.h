// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ForestMagus.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"

#include "Structs/Abilities/FMGameplayAbility.h"

#include "BTTask_ActiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UBTTask_ActiveAbility : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTTask_ActiveAbility();

	UFUNCTION(BlueprintCallable)
	void ReInitializeProbability();

	UFUNCTION(BlueprintCallable)
	TSubclassOf<UFMGameplayAbility> ActivateAbility();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Random Skill")
	bool bIsRandom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Random Skill | Abilities")
	TMap<TSubclassOf<UFMGameplayAbility>, float> AbilityMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UFMGameplayAbility> SkillAbility;
};
