
#include "Content/PlayerCharacter/PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 캐릭터 스켈레탈 메쉬 지정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
	SK_PlayerCharacter(TEXT("/Game/Characters/PlayerCharacter/SK_Cleric.SK_Cleric"));
	if (SK_PlayerCharacter.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_PlayerCharacter.Object);
	}

	// 스프링 암 지정
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);

	SpringArm->TargetArmLength = 600.f;

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;

	// 카메라 지정
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	


}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

