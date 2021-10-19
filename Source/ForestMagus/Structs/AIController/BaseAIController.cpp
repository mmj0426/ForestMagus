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
}

void ABaseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
