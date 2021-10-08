// Fill out your copyright notice in the Description page of Project Settings.


#include "Content/UMG/SkillFragmentWidget.h"
#include "Components/Image.h"

void USkillFragmentWidget::SetSkill_Icon(EFMAbilityInputID Inputkey, UTexture2D* Skill_Icon)
{
	switch (Inputkey)
	{
	case EFMAbilityInputID::Q:
		QSkill_Icon->SetBrushFromTexture(Skill_Icon);
		break;

	case EFMAbilityInputID::E:
		ESkill_Icon->SetBrushFromTexture(Skill_Icon);
		break;

	case EFMAbilityInputID::R:
		RSkill_Icon->SetBrushFromTexture(Skill_Icon);
		break;

	case EFMAbilityInputID::F:
		FSkill_Icon->SetBrushFromTexture(Skill_Icon);
		break;

	default:
		break;
	}

	FMLOG(Warning, TEXT("SkillFragmentWidget - SetSkill Icon"));
}

void USkillFragmentWidget::SetIconToDefault(EFMAbilityInputID Inputkey)
{
	switch (Inputkey)
	{
	case EFMAbilityInputID::Q:
		QSkill_Icon->SetBrushFromTexture(DefaulIconTexture);
		break;

	case EFMAbilityInputID::E:
		ESkill_Icon->SetBrushFromTexture(DefaulIconTexture);
		break;

	case EFMAbilityInputID::R:
		RSkill_Icon->SetBrushFromTexture(DefaulIconTexture);
		break;

	case EFMAbilityInputID::F:
		FSkill_Icon->SetBrushFromTexture(DefaulIconTexture);
		break;

	default:
		break;
	}
}
