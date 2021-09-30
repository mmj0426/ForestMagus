// copyright @민지

#include "Content/PlayerCharacter/PlayerCharacter.h"
#include "Content/PlayerCharacter/PlayerCharacterAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"

#include "Structs/Abilities/FMAbilitySystemComponent.h"
#include "Structs/Abilities/FMGameplayAbility.h"

#include "Structs/Enum/FMAbilityTypeEnum.h"

#include "AbilitySystemComponent.h"
#include "Components/DecalComponent.h"
#include "Camera/CameraComponent.h"

#include "Materials/Material.h"

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

	// 커서 위치에 데칼 생성
	RangeDecal = CreateDefaultSubobject<UDecalComponent>("RangeDecal");
	RangeDecal->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("/Game/Materials/Decal/M_Cursor_Decal.M_Cursor_Decal"));
	if (DecalMaterialAsset.Succeeded())
	{
		RangeDecal->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	RangeDecal->DecalSize = FVector(48.0f, 96.0f, 96.0f);
	RangeDecal->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	RangeDecal->SetHiddenInGame(true);

	bCanShowCursorDecal = false;

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

	StaffMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaffMesh"));
	StaffMesh->SetupAttachment(GetMesh(), WeaponSocket);
	StaffMesh->SetCollisionProfileName("NoCollision");

	// 무기 메쉬 세팅
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		SM_StaffWeapon(TEXT("/Game/Characters/PlayerCharacter/SM_Weapon.SM_Weapon"));
	if (SM_StaffWeapon.Succeeded())
	{
		StaffMesh->SetStaticMesh(SM_StaffWeapon.Object);
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction(TEXT("QSkill"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Q_Pressed);
	InputComponent->BindAction(TEXT("UseSkill"), EInputEvent::IE_Pressed, this, &APlayerCharacter::UseSkill_Pressed);
}

void APlayerCharacter::EndRangeSkill()
{
	// Clear Ability
	//auto ActivatableSkillArray = AbilitySystemComponent->GetActivatableAbilities();
	//AbilitySystemComponent->ClearAbility(ActivatableSkillArray[1].Handle);

	
	FMLOG(Warning, TEXT("EndRangeSkill"));

}

void APlayerCharacter::Q_Pressed()
{

	if (nullptr == FragmentAbilities[EFMAbilityInputID::Q])
	{
		return;
	}

	// 발사형일 경우
	if (FragmentAbilities[EFMAbilityInputID::Q].GetDefaultObject()->AbilityType == EFMAbilityType::Firing)
	{
		// Give Ability and Active Once
		if (HasAuthority() && AbilitySystemComponent)
		{
			auto AbilitySpec = FGameplayAbilitySpec(FragmentAbilities[EFMAbilityInputID::Q], GetCharacterLevel(), static_cast<int32>(FragmentAbilities[EFMAbilityInputID::Q].GetDefaultObject()->AbilityInputID), this);
			AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
		}

		FragmentAbilities[EFMAbilityInputID::Q] = nullptr;
		return;
	}
	// 범위형일 경우
	else if (FragmentAbilities[EFMAbilityInputID::Q].GetDefaultObject()->AbilityType == EFMAbilityType::Range)
	{
		ShowDecal(true);
		
		CastingID = EFMAbilityInputID::Q;
	}
}

void APlayerCharacter::UseSkill_Pressed()
{
	if (CastingID != EFMAbilityInputID::None)
	{
		// Give Ability and Active Once
		if (HasAuthority() && AbilitySystemComponent)
		{
			auto AbilitySpec = FGameplayAbilitySpec(FragmentAbilities[EFMAbilityInputID::Q], GetCharacterLevel(), static_cast<int32>(FragmentAbilities[EFMAbilityInputID::Q].GetDefaultObject()->AbilityInputID), this);
			AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
		}

		FragmentAbilities[CastingID] = nullptr;
		CastingID = EFMAbilityInputID::None;
	}
}

void APlayerCharacter::ShowDecal(bool CanShow)
{
	bCanShowCursorDecal = CanShow;
	GetRangeDecal()->SetHiddenInGame(!CanShow);
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

	//if (RangeDecal != nullptr && bCanShowCursorDecal)
	//{
	//	if (UWorld* World = GetWorld())
	//	{
	//		FHitResult HitResult;
	//		FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
	//		FVector StartLocation = SpringArm->GetComponentLocation();
	//		FVector EndLocation = SpringArm->GetComponentRotation().Vector() * 2000.0f;
	//		Params.AddIgnoredActor(this);
	//		World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
	//		FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
	//		RangeDecal->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);

	//	}
	//	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	//	{
	//		FHitResult TraceHitResult;
	//		PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
	//		FVector CursorFV = TraceHitResult.ImpactNormal;
	//		FRotator CursorR = CursorFV.Rotation();
	//		RangeDecal->SetWorldLocation(TraceHitResult.Location);
	//		RangeDecal->SetWorldRotation(CursorR);
	//	}
	//}
}

