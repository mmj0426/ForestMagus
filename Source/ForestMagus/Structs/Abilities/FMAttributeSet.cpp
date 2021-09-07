// copyright @¹ÎÁö

#include "Structs/Abilities/FMAttributeSet.h"
#include "Net/UnrealNetwork.h"

UFMAttributeSet::UFMAttributeSet()
{

}

void UFMAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UFMAttributeSet, Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME(UFMAttributeSet, MaxHealth);
	DOREPLIFETIME_CONDITION_NOTIFY(UFMAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME(UFMAttributeSet, MaxMana);
}

void UFMAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFMAttributeSet, Health, OldValue);
}

void UFMAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFMAttributeSet, MaxHealth, OldValue);
}

void UFMAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFMAttributeSet, Mana, OldValue);
}

void UFMAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFMAttributeSet, MaxMana, OldValue);
}