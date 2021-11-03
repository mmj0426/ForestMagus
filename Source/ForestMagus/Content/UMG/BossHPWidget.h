// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "Blueprint/UserWidget.h"
#include "BossHPWidget.generated.h"

class ABaseAIController;

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UBossHPWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected : 
	UPROPERTY(BlueprintReadWrite)
	ABaseAIController* BossAIController;


};
