// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "Structs/AIController/BaseAIController.h"
#include "DragonAIController.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API ADragonAIController : public ABaseAIController
{
	GENERATED_BODY()

public : 

	ADragonAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess()override;
};
