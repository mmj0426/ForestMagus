// copyright @����


#include "Content/BTT/BTT_ActiveAbility.h"

#include "Structs/Character/BaseMonster.h"
#include "Content/PlayerCharacter/PlayerCharacter.h"

#include "Structs/AIController/BaseAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Math/UnrealMathUtility.h"

UBTT_ActiveAbility::UBTT_ActiveAbility()
{
	NodeName = TEXT("Active Ability");
	bNotifyTick = true;

	bIsRandom = false;
}

EBTNodeResult::Type UBTT_ActiveAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseMonster* ControllingMonster = Cast<ABaseMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingMonster)
	{
		return EBTNodeResult::Failed;
	}

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABaseAIController::TargetKey));
	if (nullptr == PlayerCharacter)
	{
		return::EBTNodeResult::Failed;
	}

	bIsAttacking = true;

	if (bIsRandom)
	{
		TArray<TSubclassOf<UFMGameplayAbility>> RandomAbilities;

		// ������ ���
		for (auto& Ability : AbilityMap)
		{
			for (int i = 0; i < Ability.Value * 100; i++)
			{
				RandomAbilities.Emplace(Ability.Key);
			}
		}

		int32 RandomNum = FMath::RandRange(0, 99);

		ControllingMonster->ActiveAbility(RandomAbilities[RandomNum]);
	}
	else
	{
		// ������ �ƴ� ������ SkillAbility ���ุ �Ѵ�.
		ControllingMonster->ActiveAbility(SkillAbility);
	}

	ControllingMonster->OnAbilityEnd.Clear();

	// ��Ÿ�ְ� ������ Ability End
	ControllingMonster->OnAbilityEnd.AddLambda([this]()->void
		{
			FMLOG(Warning,TEXT("Montage Ended"));
			bIsAttacking = false;
		});

	return EBTNodeResult::InProgress;
}

void UBTT_ActiveAbility::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
