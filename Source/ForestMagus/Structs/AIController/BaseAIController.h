// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API ABaseAIController : public AAIController
{
	GENERATED_BODY()
	
public : 
	ABaseAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess()override;

protected : 
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;

};
