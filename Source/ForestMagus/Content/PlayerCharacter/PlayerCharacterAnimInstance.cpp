
#include "Content/PlayerCharacter/PlayerCharacterAnimInstance.h"

#include "Content/PlayerCharacter/PlayerCharacter.h"

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance()
{
	CurrentPawnSpeed = 0.f;

	// 대쉬 몽타주 세팅
	static ConstructorHelpers::FObjectFinder<UAnimMontage>
	Dash_Montage(TEXT("/Game/Animations/PlayerCharacter/Montage/avoid_front_Montage.avoid_front_Montage"));
	if (Dash_Montage.Succeeded())
	{
		DashMontage = Dash_Montage.Object;
	}

	MontageMap.Emplace(TEXT("Dash"),DashMontage);
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

void UPlayerCharacterAnimInstance::PlayAnimMontage(FString MontageName)
{
	if (!Montage_IsPlaying(MontageMap[MontageName]))
	{
		Montage_Play(MontageMap[MontageName],1.f);
	}
}
