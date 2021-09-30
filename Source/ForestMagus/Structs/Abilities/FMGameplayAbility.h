// copyright @민지
// edit 2021-09-09 @Winter : EffectContainerMap 관련 제작
#pragma once

#include "ForestMagus.h"
#include "Abilities/GameplayAbility.h"

#include "Structs/Abilities/FMAbilityInputIDEnum.h"
#include "Structs/Abilities/FMAbilityTypes.h"

#include "Structs/Enum/FMAbilityTypeEnum.h"

#include "FMGameplayAbility.generated.h"


UCLASS()
class FORESTMAGUS_API UFMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public : 
	UFMGameplayAbility();

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Ability")
	EFMAbilityInputID AbilityInputID = EFMAbilityInputID::None;
	
	/* Ability Type */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	EFMAbilityType AbilityType = EFMAbilityType::None;

	/** 태그를 Key로하는 Effect 컨테이너 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
	TMap<FGameplayTag, FFMGameplayEffectContainer> EffectContainerMap;

	/** Container Param의 게임플레이 이펙트를 나중에 사용할 수 있도록 포장하여 만든다. */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual FFMGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(const FFMGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** EffectContainerMap의 게임플레이 이펙트들을 나중에 사용할수있도록 포장하여 만든다. */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual FFMGameplayEffectContainerSpec MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** 포장된 게임플레이이펙트 컨테이너를 적용한다. */
	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FFMGameplayEffectContainerSpec& ContainerSpec);

	/** GameplayEffectMap의 게임플레이이펙트들을 적용한다. */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
};
