// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/Abilities/FMAbilitySystemComponent.h"
#include "Structs/Abilities/FMGameplayAbility.h"
#include "AbilitySystemGlobals.h"

UFMAbilitySystemComponent* UFMAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent /*= false*/)
{
	return Cast<UFMAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}
