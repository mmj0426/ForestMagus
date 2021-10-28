// copyright @¹ÎÁö


#include "Structs/AIController/BaseAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

const FName ABaseAIController::TargetKey(TEXT("Target"));

ABaseAIController::ABaseAIController()
{

}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if ((UseBlackboard(BBAsset, Blackboard)) && (!RunBehaviorTree(BTAsset)))
	{
		FMLOG(Error, TEXT("AI Controller couldn't run behavior tree!"));
	}
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
