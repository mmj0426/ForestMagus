
#include "Content/PlayerCharacter/PlayerCharacterAnimInstance.h"

#include "Content/PlayerCharacter/PlayerCharacter.h"

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance()
{
	CurrentPawnSpeed = 0.f;
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* const Player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (::IsValid(TryGetPawnOwner()))
	{
		CurrentPawnSpeed = Player->GetVelocity().Size();
	}
}