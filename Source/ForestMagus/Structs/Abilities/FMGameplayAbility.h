// copyright @����
// edit 2021-09-09 @Winter : EffectContainerMap ���� ����
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

	/** �±׸� Key���ϴ� Effect �����̳� */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
	TMap<FGameplayTag, FFMGameplayEffectContainer> EffectContainerMap;

	/** Container Param�� �����÷��� ����Ʈ�� ���߿� ����� �� �ֵ��� �����Ͽ� �����. */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual FFMGameplayEffectContainerSpec MakeEffectContainerSpecFromContainer(const FFMGameplayEffectContainer& Container, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** EffectContainerMap�� �����÷��� ����Ʈ���� ���߿� ����Ҽ��ֵ��� �����Ͽ� �����. */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual FFMGameplayEffectContainerSpec MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);

	/** ����� �����÷�������Ʈ �����̳ʸ� �����Ѵ�. */
	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainerSpec(const FFMGameplayEffectContainerSpec& ContainerSpec);

	/** GameplayEffectMap�� �����÷�������Ʈ���� �����Ѵ�. */
	UFUNCTION(BlueprintCallable, Category = Ability, meta = (AutoCreateRefTerm = "EventData"))
	virtual TArray<FActiveGameplayEffectHandle> ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData, int32 OverrideGameplayLevel = -1);
};
