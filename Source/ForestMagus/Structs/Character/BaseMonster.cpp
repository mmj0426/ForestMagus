// copyright @¹ÎÁö


#include "Structs/Character/BaseMonster.h"

#include "Structs//AIController/BaseAIController.h"
#include "Structs/AnimInstance/BaseCharacterAnimInstance.h"

#include "Structs/Abilities/FMAbilitySystemComponent.h"
#include "Structs/Abilities/FMGameplayAbility.h"

ABaseMonster::ABaseMonster()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABaseMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MonsterAnim = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	FMCHECK(MonsterAnim != nullptr);

	MonsterAnim->OnMontageEnded.AddDynamic(this,&ABaseMonster::MontageEnded);
}

void ABaseMonster::ActiveAbility(TSubclassOf<UFMGameplayAbility> SkillAbility)
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		auto AbilitySpec = FGameplayAbilitySpec(SkillAbility, GetCharacterLevel(), static_cast<int32>(SkillAbility.GetDefaultObject()->AbilityInputID), this);
		AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void ABaseMonster::MontageEnded(UAnimMontage* Montage, bool bInterrupeted)
{
	FMLOG(Warning, TEXT("BaseMonster"));
	OnAbilityEnd.Broadcast();
}
