// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "GameFramework/HUD.h"
#include "DungeonHUD.generated.h"

class USkillFragmentWidget;

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API ADungeonHUD : public AHUD
{
	GENERATED_BODY()

public : 
	ADungeonHUD();

	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, Category = "UMG")
	TSubclassOf<USkillFragmentWidget> SkillFragmentWidget;

	UPROPERTY(EditAnywhere, Category = "UMG")
	TSubclassOf<UUserWidget> DeathWidget;

	UFUNCTION(BlueprintCallable)
	USkillFragmentWidget* GetSkillFragmentWidget();

	UFUNCTION(BlueprintCallable)
	UUserWidget* GetDeathWidget();

private:
	UPROPERTY()
	class USkillFragmentWidget* SkillFragmentWidgetClass;
	
	UPROPERTY()
	class UUserWidget* DeathWidgetClass;
};
