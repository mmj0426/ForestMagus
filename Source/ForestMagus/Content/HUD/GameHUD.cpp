// Fill out your copyright notice in the Description page of Project Settings.


#include "Content/HUD/GameHUD.h"

#include "Content/UMG/SkillFragmentWidget.h"

AGameHUD::AGameHUD()
{

}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (SkillFragmentWidgetClass)
	{
		SkillFragmentWidget = CreateWidget<USkillFragmentWidget>(GetWorld(),SkillFragmentWidgetClass);
		if (SkillFragmentWidget)
		{
			SkillFragmentWidget->AddToViewport();
		}
	}
}

USkillFragmentWidget* AGameHUD::GetSkillFragmentWidget()
{
	return SkillFragmentWidget;
}
