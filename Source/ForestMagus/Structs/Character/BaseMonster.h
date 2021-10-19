// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ForestMagus.h"
#include "Structs/Character/BaseCharacter.h"
#include "BaseMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAbilityEndDelegate);

UCLASS()
class FORESTMAGUS_API ABaseMonster : public ABaseCharacter
{
	GENERATED_BODY()

public : 

	ABaseMonster();
	virtual void PostInitializeComponents()override;

public : 

	// BTT���� �����Ƽ ����
	void ActiveAbility(TSubclassOf<UFMGameplayAbility> SkillAbility);

	// �ִϸ��̼�

	UPROPERTY()
	class UBaseCharacterAnimInstance* MonsterAnim;

	FOnAbilityEndDelegate OnAbilityEnd;

	UFUNCTION()
	void MontageEnded(UAnimMontage* Montage, bool bInterrupeted);

};
