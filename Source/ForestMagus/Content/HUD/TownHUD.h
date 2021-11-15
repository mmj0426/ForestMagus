// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "GameFramework/HUD.h"
#include "TownHUD.generated.h"

/**
 * 
 */

UCLASS()
class FORESTMAGUS_API ATownHUD : public AHUD
{
	GENERATED_BODY()

public : 
	ATownHUD();

	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, Category = "UMG")
	TSubclassOf<UUserWidget> DialogueWidget;

	UUserWidget* GetDialogueWidget();

private : 

	UPROPERTY()
	class UUserWidget* DialogueWidgetClass;
	
};
