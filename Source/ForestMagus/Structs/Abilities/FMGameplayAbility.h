// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "Abilities/GameplayAbility.h"
#include "Structs/Abilities/FMAbilityInputIDEnum.h"
#include "FMGameplayAbility.generated.h"


UCLASS()
class FORESTMAGUS_API UFMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public : 
	UFMGameplayAbility();

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Ability")
	EFMAbilityInputID AbilityInputID = EFMAbilityInputID::None;
	
};
