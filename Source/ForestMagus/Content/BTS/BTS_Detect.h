// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "BehaviorTree/BTService.h"
#include "BTS_Detect.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UBTS_Detect : public UBTService
{
	GENERATED_BODY()

public:

	UBTS_Detect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectRadius;


protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
};
