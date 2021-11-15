// copyright @¹ÎÁö


#include "Content/HUD/DungeonHUD.h"

#include "Content/UMG/SkillFragmentWidget.h"


ADungeonHUD::ADungeonHUD()
{

}

void ADungeonHUD::BeginPlay()
{
	Super::BeginPlay();

	if (SkillFragmentWidget)
	{
		SkillFragmentWidgetClass = CreateWidget<USkillFragmentWidget>(GetWorld(), SkillFragmentWidget);
		if (SkillFragmentWidgetClass)
		{
			SkillFragmentWidgetClass->AddToViewport();
		}
	}
}

USkillFragmentWidget* ADungeonHUD::GetSkillFragmentWidget()
{
	return SkillFragmentWidgetClass;
}
