// Fill out your copyright notice in the Description page of Project Settings.

// copyright @Winter

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Structs/Abilities/FMAbilityTypes.h"

#include "FMBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UFMBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/** �̹� ����� Effect�����̳ʸ� ������ Target�� �߰��Ѵ�. */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "HitResults,TargetActors"))
	static FFMGameplayEffectContainerSpec AddTargetsToEffectContainerSpec(const FFMGameplayEffectContainerSpec& ContainerSpec, const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);

	/** �̹� ����� Effect�����̳ʸ� Target������ �����Ѵ�. */
	UFUNCTION(BlueprintCallable, Category = Ability)
	static TArray<FActiveGameplayEffectHandle> ApplyExternalEffectContainerSpec(const FFMGameplayEffectContainerSpec& ContainerSpec);
};
