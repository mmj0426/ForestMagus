// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ForestMagus.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class USkillFragmentWidget;

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public : 
	AGameHUD();

	virtual void BeginPlay();

	UPROPERTY(EditAnywhere, Category = "UMG")
	TSubclassOf<USkillFragmentWidget> SkillFragmentWidgetClass;

	USkillFragmentWidget* GetSkillFragmentWidget();

private : 
	UPROPERTY()
	class USkillFragmentWidget* SkillFragmentWidget;

};
