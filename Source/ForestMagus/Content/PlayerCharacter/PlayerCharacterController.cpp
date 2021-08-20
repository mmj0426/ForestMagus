
#include "Content/PlayerCharacter/PlayerCharacterController.h"

#include "Content/PlayerCharacter/PlayerCharacter.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	FMPlayer = Cast<APlayerCharacter>(GetPawn());
}

void APlayerCharacterController::Tick(float DeltaTime)
{
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacterController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacterController::MoveRight);
}

void APlayerCharacterController::MoveForward(float NewAxisValue)
{
	if (FMPlayer && NewAxisValue != 0.f)
	{
		FMPlayer->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::X),NewAxisValue);
	}
}

void APlayerCharacterController::MoveRight(float NewAxisValue)
{
	if (FMPlayer && NewAxisValue != 0.f)
	{
		FMPlayer->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), NewAxisValue);
	}
}
