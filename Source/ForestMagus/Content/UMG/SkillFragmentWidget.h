// copyright @¹ÎÁö
#pragma once

#include "ForestMagus.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Abilities/FMAbilityInputIDEnum.h"
#include "SkillFragmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API USkillFragmentWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected : 
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* QSkill_Icon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ESkill_Icon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* RSkill_Icon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* FSkill_Icon;

	UPROPERTY(BlueprintReadWrite)
	class UTexture2D* DefaulIconTexture;
	
public : 

	void SetSkill_Icon(EFMAbilityInputID Inputkey, UTexture2D* Skill_Icon);

	void SetIconToDefault(EFMAbilityInputID Inputkey);
};
