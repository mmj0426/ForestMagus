
#include "Content/PlayerCharacter/PlayerCharacterController.h"

#include "Content/PlayerCharacter/PlayerCharacter.h"

#include "Runtime/Engine/Classes/Components/DecalComponent.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	FMPlayer = Cast<APlayerCharacter>(GetPawn());
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacterController::SetupInputComponent()
{

	Super::SetupInputComponent();

	// 축 매핑 바인드
	InputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacterController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacterController::MoveRight);

	InputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacterController::LookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacterController::Turn);

	// 액션 매핑 바인드
	InputComponent->BindAction(TEXT("Teleportation"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::Teleportation);
	InputComponent->BindAction(TEXT("Meteor"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::Q_Pressed);
	InputComponent->BindAction(TEXT("UseSkill"), EInputEvent::IE_Pressed, this, &APlayerCharacterController::UseSkill);
}

void APlayerCharacterController::MoveForward(float NewAxisValue)
{
	MoveValue.X = NewAxisValue;
	if (FMPlayer && NewAxisValue != 0.f)
	{
		FMPlayer->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::X), NewAxisValue);
	}
}

void APlayerCharacterController::MoveRight(float NewAxisValue)
{
	MoveValue.Y = NewAxisValue;
	if (FMPlayer && NewAxisValue != 0.f)
	{
		FMPlayer->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), NewAxisValue);
	}
}

void APlayerCharacterController::LookUp(float NewAxisValue)
{
	if (FMPlayer && NewAxisValue != 0.f)
	{
		FMPlayer->AddControllerPitchInput(NewAxisValue);
	}
}

void APlayerCharacterController::Turn(float NewAxisValue)
{
	if (FMPlayer && NewAxisValue != 0.f)
	{
		FMPlayer->AddControllerYawInput(NewAxisValue);
	}
}

void APlayerCharacterController::RotateCharacter()
{
	int32 MoveValueX = static_cast<int32>(MoveValue.X);
	int32 MoveValueY = static_cast<int32>(MoveValue.Y);

	int32 RotationRate = 0;

	if (MoveValueX != 0 && MoveValueY == 0)
	{
		RotationRate = MoveValueX < 0 ? 180 : 0;
	}
	else
	{
		RotationRate = MoveValueY * (90 + -(MoveValueX * 45));
	}

	FMPlayer->SetActorRotation(FRotator(0.f, GetControlRotation().Yaw + RotationRate, 0.f));
}

void APlayerCharacterController::Teleportation()
{
	RotateCharacter();

	FMPlayer->Teleportation();
}

void APlayerCharacterController::Q_Pressed()
{
	FMPlayer->bCanShowCursorDecal = true;
	FMPlayer->GetCursorToWorld()->SetHiddenInGame(false);
}

void APlayerCharacterController::UseSkill()
{
	FMPlayer->bCanShowCursorDecal = false;
	FMPlayer->GetCursorToWorld()->SetHiddenInGame(true);
}
