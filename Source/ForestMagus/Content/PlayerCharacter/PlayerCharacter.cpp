// copyright @����

#include "Content/PlayerCharacter/PlayerCharacter.h"
#include "Content/PlayerCharacter/PlayerCharacterAnimInstance.h"

#include "Content/HUD/GameHUD.h"
#include "Content/UMG/SkillFragmentWidget.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"

#include "Structs/Abilities/FMAbilitySystemComponent.h"
#include "Structs/Abilities/FMGameplayAbility.h"
#include "Structs/Enum/FMAbilityTypeEnum.h"

#include "AbilitySystemComponent.h"

#include "Components/DecalComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Camera/CameraComponent.h"

#include "Materials/Material.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// ĳ���� ���̷�Ż �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_PlayerCharacter(TEXT("/Game/Characters/PlayerCharacter/SK_PlayerCharacter.SK_PlayerCharacter"));
	if (SK_PlayerCharacter.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_PlayerCharacter.Object);
	}

	// ������ �� ����
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator::ZeroRotator);

	SpringArm->TargetArmLength = 600.f;

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;

	// ī�޶� ����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Ŀ�� ��ġ�� ��Į ����
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

	// �ִϸ��̼� ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		Player_AnimBP(TEXT("/Game/Animations/PlayerCharacter/AnimBP_PlayerCharacter.AnimBP_PlayerCharacter_C"));
	if (Player_AnimBP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Player_AnimBP.Class);
	}

	// ���Ͽ� ���� ����
	FName WeaponSocket(TEXT("Weapon"));

	StaffMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaffMesh"));
	StaffMesh->SetupAttachment(GetMesh(), WeaponSocket);
	StaffMesh->SetCollisionProfileName("NoCollision");

	// ���� �޽� ����
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
	
	InputComponent->BindAction(TEXT("FragmentSkill"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SeparateSkillKey);

	InputComponent->BindAction(TEXT("UseSkill"), EInputEvent::IE_Pressed, this, &APlayerCharacter::UseSkill_Pressed);
	InputComponent->BindAction(TEXT("BasicAttack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::BasicAttack);
}

void APlayerCharacter::EndRangeSkill()
{
	// Clear Ability
	//auto ActivatableSkillArray = AbilitySystemComponent->GetActivatableAbilities();
	//AbilitySystemComponent->ClearAbility(ActivatableSkillArray[1].Handle);

	FMLOG(Warning, TEXT("EndRangeSkill"));

}

void APlayerCharacter::OnSkillKeyPressed()
{
	if (nullptr == FragmentAbilities[InputKey])
	{
		return;
	}

	// �߻����� ���
	if (FragmentAbilities[InputKey].GetDefaultObject()->AbilityType == EFMAbilityType::Firing)
	{
		// Give Ability and Active Once
		if (HasAuthority() && AbilitySystemComponent)
		{
			auto AbilitySpec = FGameplayAbilitySpec(FragmentAbilities[InputKey], GetCharacterLevel(), static_cast<int32>(FragmentAbilities[InputKey].GetDefaultObject()->AbilityInputID), this);
			AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
		}

		// UI�� ����ִ�(Default) �̹����� �ٲ���
		auto SkillFragmentWidget = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->GetSkillFragmentWidget();
		SkillFragmentWidget->SetIconToDefault(InputKey);

		FragmentAbilities[InputKey] = nullptr;

		return;
	}
	// �������� ���
	else if (FragmentAbilities[InputKey].GetDefaultObject()->AbilityType == EFMAbilityType::Range)
	{
		ShowDecal(true);
		
		CastingID = InputKey;
	}
}

void APlayerCharacter::UseSkill_Pressed()
{
	if (CastingID != EFMAbilityInputID::None)
	{
		// Give Ability and Active Once
		if (HasAuthority() && AbilitySystemComponent)
		{
			auto AbilitySpec = FGameplayAbilitySpec(FragmentAbilities[InputKey], GetCharacterLevel(), static_cast<int32>(FragmentAbilities[InputKey].GetDefaultObject()->AbilityInputID), this);
			AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
		}

		FragmentAbilities[CastingID] = nullptr;

		// UI�� ����ִ�(Default) �̹����� �ٲ���
		auto SkillFragmentWidget = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->GetSkillFragmentWidget();
		SkillFragmentWidget->SetIconToDefault(InputKey);

		CastingID = EFMAbilityInputID::None;
	}
}

void APlayerCharacter::BasicAttack()
{
	if (CastingID != EFMAbilityInputID::None)
	{
		// Cancel range attack
		ShowDecal(false);
		CastingID = EFMAbilityInputID::None;

		FMLOG(Warning, TEXT("Cancel the RangeSkill"));

	}
	
	// And play basic attack 
	if (HasAuthority() && AbilitySystemComponent)
	{
		auto AbilitySpec = FGameplayAbilitySpec(BasicAttackAbility, GetCharacterLevel(), static_cast<int32>(BasicAttackAbility.GetDefaultObject()->AbilityInputID), this);
		AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
	}

}

void APlayerCharacter::SeparateSkillKey(FKey key)
{
	// Ű �Է� �и�
	FName KeyName = key.GetFName();

	if (KeyName.ToString() == TEXT("Q"))
	{
		InputKey = EFMAbilityInputID::Q;
	}
	else if (KeyName.ToString() == TEXT("E"))
	{
		InputKey = EFMAbilityInputID::E;
	}
	else if (KeyName.ToString() == TEXT("R"))
	{
		InputKey = EFMAbilityInputID::R;
	}

	OnSkillKeyPressed();
}

void APlayerCharacter::SetAbility(TSubclassOf<UFMGameplayAbility> SkillAbility, UTexture2D* SkillIcon)
{
	EFMAbilityInputID SkillSlot;
	
	// ��ų ������ ����ִ� ���¸� Q > E > R ������ ä���.
	if (FragmentAbilities[EFMAbilityInputID::Q] == nullptr)
	{
		FragmentAbilities[EFMAbilityInputID::Q] = SkillAbility;
		SkillSlot = EFMAbilityInputID::Q;
	}
	else if (FragmentAbilities[EFMAbilityInputID::E] == nullptr)
	{
		FragmentAbilities[EFMAbilityInputID::E] = SkillAbility;
		SkillSlot = EFMAbilityInputID::E;
	}
	else if (FragmentAbilities[EFMAbilityInputID::R] == nullptr)
	{
		FragmentAbilities[EFMAbilityInputID::R] = SkillAbility;
		SkillSlot = EFMAbilityInputID::R;
	}

	// �ش� Ű�� �ش��ϴ� ��ų ���� UI�� ��ų �������� ���������
	auto SkillFragmentWidget = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD())->GetSkillFragmentWidget();
	SkillFragmentWidget->SetSkill_Icon(SkillSlot,SkillIcon);
}

bool APlayerCharacter::CanGetSkillFragment()
{
	for (auto it = FragmentAbilities.CreateConstIterator(); it; ++it)
	{
		if (*it.Value() == nullptr)
		{
			return true;
		}
	}

	return false;
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

	FragmentAbilities.Emplace(EFMAbilityInputID::Q,nullptr);
	FragmentAbilities.Emplace(EFMAbilityInputID::E, nullptr);
	FragmentAbilities.Emplace(EFMAbilityInputID::R, nullptr);
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

