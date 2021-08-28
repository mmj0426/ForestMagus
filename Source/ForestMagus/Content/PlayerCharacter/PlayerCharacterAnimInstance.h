#pragma once

#include "ForestMagus.h"
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

	void PlayAnimMontage(FString MontageName);

protected :
	
	// 플레이어 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn)
	float CurrentPawnSpeed;

	// 몽타주
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
	TMap<FString, UAnimMontage*> MontageMap;


};
