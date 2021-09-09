// copyright @민지

#include "Content/PlayerCharacter/PlayerCharacter.h"
#include "Content/PlayerCharacter/PlayerCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// 캐릭터 스켈레탈 메쉬 지정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
	SK_PlayerCharacter(TEXT("/Game/Characters/PlayerCharacter/SK_PlayerCharacter.SK_PlayerCharacter"));
	if (SK_PlayerCharacter.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_PlayerCharacter.Object);
	}

	// 스프링 암 세팅
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);

	SpringArm->TargetArmLength = 600.f;

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;

	// 카메라 세팅
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	// 애니메이션 세팅
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
	Player_AnimBP(TEXT("/Game/Animations/PlayerCharacter/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C"));
	if (Player_AnimBP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Player_AnimBP.Class);
	}

	// 소켓에 무기 세팅
	FName WeaponSocket(TEXT("Weapon"));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh(),WeaponSocket);
	WeaponMesh->SetCollisionProfileName("NoCollision");

	// 무기 메쉬 세팅
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
	SM_StaffWeapon(TEXT("/Game/Characters/PlayerCharacter/SM_Weapon.SM_Weapon"));
	if (SM_StaffWeapon.Succeeded())
	{
		WeaponMesh->SetStaticMesh(SM_StaffWeapon.Object);
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PlayerAnim = Cast<UPlayerCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	FMCHECK(nullptr != PlayerAnim);
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

