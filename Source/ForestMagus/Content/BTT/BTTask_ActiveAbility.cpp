// Fill out your copyright notice in the Description page of Project Settings.


#include "Content/BTT/BTTask_ActiveAbility.h"

UBTTask_ActiveAbility::UBTTask_ActiveAbility()
{
	NodeName = TEXT("Active Ability");

	bIsRandom = false;
}

void UBTTask_ActiveAbility::ReInitializeProbability()
{
	float ProbSum = 0.f;
	for (auto& Ability : AbilityMap)
	{
		ProbSum += Ability.Value;
	}

	for (auto& Ability : AbilityMap)
	{
		Ability.Value = Ability.Value / ProbSum;
	}
}

TSubclassOf<UFMGameplayAbility> UBTTask_ActiveAbility::ActivateAbility()
{
	float RandomKey = FMath::RandRange(0.f, 1.f);

	float ProbSum = 0.f;
	for (auto& Ability : AbilityMap)
	{
		ProbSum += Ability.Value;
		if (ProbSum >= RandomKey)
		{
			return Ability.Key;
		}
	}

	return nullptr;
}
