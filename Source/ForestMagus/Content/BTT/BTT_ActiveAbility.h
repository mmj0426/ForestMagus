// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "BehaviorTree/BTTaskNode.h"

#include "Structs/Abilities/FMGameplayAbility.h"

#include "BTT_ActiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UBTT_ActiveAbility : public UBTTaskNode
{
	GENERATED_BODY()

public : 

	UBTT_ActiveAbility();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public : 
	
	UPROPERTY(EditAnywhere,Category = "Random Skill")
	bool bIsRandom;

	UPROPERTY(EditAnywhere, Category = "Random Skill | Abilities")
	TMap<TSubclassOf<UFMGameplayAbility>,float> AbilityMap;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UFMGameplayAbility> SkillAbility;

private : 

	bool bIsAttacking;
	

};
