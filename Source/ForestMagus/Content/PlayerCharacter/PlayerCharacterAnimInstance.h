#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public : 
	UPlayerCharacterAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected :

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn)
	float CurrentPawnSpeed;
	
};
