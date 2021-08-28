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
	
	// �÷��̾� �ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Pawn)
	float CurrentPawnSpeed;

	// ��Ÿ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Montage)
	TMap<FString, UAnimMontage*> MontageMap;


};
