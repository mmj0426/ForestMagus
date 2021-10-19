// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ForestMagus.h"
#include "Animation/AnimInstance.h"
#include "BaseCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UBaseCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBaseCharacterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	// ���� �ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn)
	float CurrentPawnSpeed;
};
