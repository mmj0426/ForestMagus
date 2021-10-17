// copyright @민지


#include "Content/Monster/DragonAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

ADragonAIController::ADragonAIController()
{
	// 블랙보드 연결
	static ConstructorHelpers::FObjectFinder<UBlackboardData>
	BBObject(TEXT("/Game/BehaviorTree/Dragon/BB_Dragon.BB_Dragon"));
	if(BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	// 비헤이비어트리 연결
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
	BTObject(TEXT("/Game/BehaviorTree/Dragon/BT_Dragon.BT_Dragon"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

}

void ADragonAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if ((UseBlackboard(BBAsset, Blackboard)) && (!RunBehaviorTree(BTAsset)))
	{
		FMLOG(Error, TEXT("AI Controller couldn't run behavior tree!"));
	}
}

void ADragonAIController::OnUnPossess()
{
}
