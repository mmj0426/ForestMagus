// copyright @¹ÎÁö


#include "Structs/AnimInstance/BaseCharacterAnimInstance.h"

#include "Structs/Character/BaseCharacter.h"


UBaseCharacterAnimInstance::UBaseCharacterAnimInstance()
{
	CurrentPawnSpeed = 0.f;
}

void UBaseCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ABaseCharacter* const Character = Cast<ABaseCharacter>(TryGetPawnOwner());

	if (::IsValid(TryGetPawnOwner()))
	{
		CurrentPawnSpeed = Character->GetVelocity().Size();
	}
}

