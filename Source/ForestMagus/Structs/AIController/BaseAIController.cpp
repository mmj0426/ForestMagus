// copyright @¹ÎÁö


#include "Structs/AIController/BaseAIController.h"

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
