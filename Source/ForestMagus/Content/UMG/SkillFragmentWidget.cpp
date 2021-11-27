// copyright @¹ÎÁö


#include "Content/UMG/SkillFragmentWidget.h"
#include "Content/PlayerCharacter/PlayerCharacterController.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void USkillFragmentWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USkillFragmentWidget::SetSkill_Icon(EFMAbilityInputID Inputkey, UMaterial* Skill_Icon)
{
	switch (Inputkey)
	{
	case EFMAbilityInputID::Q:
		QSkill_Icon->SetBrushFromMaterial(Skill_Icon);
		break;

	case EFMAbilityInputID::E:
		ESkill_Icon->SetBrushFromMaterial(Skill_Icon);
		break;

	case EFMAbilityInputID::R:
		RSkill_Icon->SetBrushFromMaterial(Skill_Icon);
		break;

	case EFMAbilityInputID::F:
		FSkill_Icon->SetBrushFromMaterial(Skill_Icon);
		break;

	default:
		break;
	}

	FMLOG(Warning, TEXT("SkillFragmentWidgetClass - SetSkill Icon")) ;
}

void USkillFragmentWidget::SetIconToDefault(EFMAbilityInputID Inputkey)
{
	switch (Inputkey)
	{
	case EFMAbilityInputID::Q:
		QSkill_Icon->SetBrushFromMaterial(DefaulIconTexture);
		break;

	case EFMAbilityInputID::E:
		ESkill_Icon->SetBrushFromMaterial(DefaulIconTexture);
		break;

	case EFMAbilityInputID::R:
		RSkill_Icon->SetBrushFromMaterial(DefaulIconTexture);
		break;

	case EFMAbilityInputID::F:
		FSkill_Icon->SetBrushFromMaterial(DefaulIconTexture);
		break;

	default:
		break;
	}
}

void USkillFragmentWidget::SetPlayerHealthPercent(float CurrentHealthPercent)
{
	PlayerHealth = CurrentHealthPercent;
}

void USkillFragmentWidget::SetPlayerManaPercent(float CurrentManaPercent)
{
	PlayerMana = CurrentManaPercent;
}
