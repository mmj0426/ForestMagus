// copyright @민지
// 
// edit 2021-10-15 @Winter
// BP에 있는 Tick 로직 CPP로 변경 (성능 차이의 이유로 변경)

#include "Content/PlayerCharacter/PlayerCharacter.h"

#include "Content/HUD/DungeonHUD.h"

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
#include <Kismet/KismetMathLibrary.h>

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
	//static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("/Game/StylizedVFX-AirStrikes/Materials/MaterialInstances/MI_Circle_01.MI_Circle_01"));
	//if (DecalMaterialAsset.Succeeded())
	//{
	//	RangeDecal->SetDecalMaterial(DecalMaterialAsset.Object);
	//}
	//RangeDecal->DecalSize = FVector(48.0f, 96.0f, 96.0f);
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

	CurrentState = EFMPlayerState::None;

	CanNPCInteraction = false;

	bIsCooldown = false;
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

//void APlayerCharacter::EndRangeSkill()
//{
//	// Clear Ability
//	//auto ActivatableSkillArray = AbilitySystemComponent->GetActivatableAbilities();
//	//AbilitySystemComponent->ClearAbility(ActivatableSkillArray[1].Handle);
//
//	FMLOG(Warning, TEXT("EndRangeSkill"));
//
//}

bool APlayerCharacter::GetCrosshairHitResult(FHitResult& Result)
{
	FVector CameraLocation = Camera->GetComponentLocation();
	FRotator CameraRotation = Camera->GetComponentRotation();

	FVector Forward = UKismetMathLibrary::GetForwardVector(CameraRotation) * 5000.f;

	FHitResult HitResult;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	EDrawDebugTrace::Type Debug = EDrawDebugTrace::None;
	if (bCrosshairDebug)
	{
		Debug = EDrawDebugTrace::ForDuration;
	}

	bool bResult = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), CameraLocation, Forward + CameraLocation, CrosshairObjectTypes,
		true, ActorsToIgnore, Debug, HitResult, true);

	if (bResult)
	{
		Result = HitResult;
	}

	return bResult;
}

void APlayerCharacter::OnSkillKeyPressed()
{
	if (nullptr == FragmentAbilities[InputKey])
	{
		return;
	}

	if (InputKey == EFMAbilityInputID::F)
	{
		if (!bIsCooldown)
		{
			if (FragmentAbilities[InputKey].GetDefaultObject()->AbilityType == EFMAbilityType::Range)
			{
				ShowDecal(true);

				CastingID = InputKey;
			}
		}
		else return;

	}
	else
	{
		// 발사형일 경우
		if (FragmentAbilities[InputKey].GetDefaultObject()->AbilityType == EFMAbilityType::Firing)
		{
			// Give Ability and Active Once
			if (HasAuthority() && AbilitySystemComponent)
			{
				auto AbilitySpec = FGameplayAbilitySpec(FragmentAbilities[InputKey], GetCharacterLevel(), static_cast<int32>(FragmentAbilities[InputKey].GetDefaultObject()->AbilityInputID), this);
				AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
			}

			// UI를 비어있는(Default) 이미지로 바꿔줌
			auto SkillFragmentWidget = Cast<ADungeonHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->GetSkillFragmentWidget();
			SkillFragmentWidget->SetIconToDefault(InputKey);

			FragmentAbilities[InputKey] = nullptr;

			return;
		}
		// 범위형일 경우
		else if (FragmentAbilities[InputKey].GetDefaultObject()->AbilityType == EFMAbilityType::Range)
		{
			ShowDecal(true);

			CastingID = InputKey;
		}
	}

}

void APlayerCharacter::UseSkill_Pressed()
{
	if (CastingID != EFMAbilityInputID::None)
	{
		// 고정스킬일 경우 GiveAbility
		if (CastingID == EFMAbilityInputID::F && HasAuthority() && AbilitySystemComponent)
		{
			auto AbilitySpec = FGameplayAbilitySpec(FragmentAbilities[InputKey], GetCharacterLevel(), static_cast<int32>(FragmentAbilities[InputKey].GetDefaultObject()->AbilityInputID), this);
			AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);

			bIsCooldown = true;
			CastingID = EFMAbilityInputID::None;

			GetWorldTimerManager().SetTimer(SkillCooldown_TimerHandle, [&]()
				{
					FMLOG(Warning, TEXT("bIsCooltime is false"));
					bIsCooldown = false;
					GetWorldTimerManager().ClearTimer(SkillCooldown_TimerHandle);
				}, Cooldown, true);

		}
		// Give Ability and Active Once
		else if (HasAuthority() && AbilitySystemComponent)
		{
			auto AbilitySpec = FGameplayAbilitySpec(FragmentAbilities[InputKey], GetCharacterLevel(), static_cast<int32>(FragmentAbilities[InputKey].GetDefaultObject()->AbilityInputID), this);
			AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);


			FragmentAbilities[CastingID] = nullptr;

			//UI를 비어있는(Default) 이미지로 바꿔줌
			auto HUD = Cast<ADungeonHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
			if (HUD != nullptr)
			{
				HUD->GetSkillFragmentWidget()->SetIconToDefault(InputKey);
			}

			CastingID = EFMAbilityInputID::None;
		}

		ShowDecal(false);

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
	// 키 입력 분리
	if (CastingID == EFMAbilityInputID::None)
	{
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
		else if (KeyName.ToString() == TEXT("F"))
		{
			InputKey = EFMAbilityInputID::F;
		}


		OnSkillKeyPressed();
	}

}

void APlayerCharacter::SetAbility(bool IsFixedSkill, TSubclassOf<UFMGameplayAbility> SkillAbility, UMaterial* SkillIcon)
{
	EFMAbilityInputID SkillSlot;

	if (IsFixedSkill)
	{
		if (FragmentAbilities[EFMAbilityInputID::F] == nullptr)
		{
			FragmentAbilities[EFMAbilityInputID::F] = SkillAbility;
			SkillSlot = EFMAbilityInputID::F;
		}
	}
	else
	{
		// 스킬 슬롯이 비어있는 상태면 Q > E > R 순으로 채운다.
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
	}

	// 해당 키에 해당하는 스킬 슬롯 UI에 스킬 아이콘을 적용시켜줌
	auto HUD = Cast<ADungeonHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (HUD != nullptr)
	{
		HUD->GetSkillFragmentWidget()->SetSkill_Icon(SkillSlot, SkillIcon);
	}
}

bool APlayerCharacter::CanGetSkillFragment() const
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

void APlayerCharacter::DrawRangeDecal()
{
	if (false == bCanShowCursorDecal)
	{
		return;
	}

	FHitResult HitResult;
	bool bResult = GetCrosshairHitResult(HitResult);

	if (bResult)
	{
		FVector ImpactNormal = HitResult.ImpactNormal;

		RangeDecal->SetWorldLocationAndRotation(HitResult.Location, ImpactNormal.ToOrientationQuat());
	}
}

bool APlayerCharacter::CanMove() const
{
	return ((CurrentState != EFMPlayerState::Teleportation)
		&& (CurrentState != EFMPlayerState::Attacking)
		&& (CurrentState != EFMPlayerState::Conversation));
}

bool APlayerCharacter::CanTeleportation() const
{
	// TODO : && (GetCurrentMana() >= 텔레포트 사용 마나..)
	return ((CurrentState != EFMPlayerState::Attacking)
		&& (CurrentState != EFMPlayerState::Conversation)
		&& ((GetCurrentMana() >= 20.f) ? true : false)
		&& (!CanNPCInteraction));
}

void APlayerCharacter::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	auto PlayerController = Cast<APlayerController>(GetController());
	auto HUD = Cast<ADungeonHUD>(PlayerController->GetHUD());

	if (HUD != nullptr)
	{
		HUD->GetSkillFragmentWidget()->SetPlayerHealthPercent(FMath::Clamp<float>((GetCurrentHealth() / GetMaxHealth()), 0.f, 1.f));

		// Death
		if (GetCurrentHealth() <= 0.f)
		{
			bIsAlive = false;
			HUD->GetDeathWidget()->AddToViewport();

			Death();
		}
	}
}

void APlayerCharacter::HandleManaChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	auto PlayerController = Cast<APlayerController>(GetController());
	auto HUD = Cast<ADungeonHUD>(PlayerController->GetHUD());
	if (HUD != nullptr)
	{
		HUD->GetSkillFragmentWidget()->SetPlayerManaPercent(FMath::Clamp<float>((GetCurrentMana() / GetMaxMana()), 0.f, 1.f));
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

	//PlayerAnim = Cast<UBaseCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	//FMCHECK(nullptr != PlayerAnim);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// HP Widget : PlayerHealth Percent -> 1
	// TODO : 게임모드가 DungeonGameMode일 때만 
	{
		auto PlayerController = Cast<APlayerController>(GetController());
		auto HUD = Cast<ADungeonHUD>(PlayerController->GetHUD());
		if (HUD != nullptr)
		{
			HUD->GetSkillFragmentWidget()->SetPlayerHealthPercent(1.f);
			HUD->GetSkillFragmentWidget()->SetPlayerManaPercent(1.f);
		}

	}

	FragmentAbilities.Emplace(EFMAbilityInputID::Q, nullptr);
	FragmentAbilities.Emplace(EFMAbilityInputID::E, nullptr);
	FragmentAbilities.Emplace(EFMAbilityInputID::R, nullptr);
	FragmentAbilities.Emplace(EFMAbilityInputID::F, nullptr);

	GetWorldTimerManager().SetTimer(RecoverMana_TimerHandle, this, &APlayerCharacter::RecoverMana, 1.f, true);
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndplayReason)
{
	// 타이머 해제
	if (GetWorldTimerManager().IsTimerActive(RecoverMana_TimerHandle))
	{
		GetWorldTimerManager().ClearTimer(RecoverMana_TimerHandle);
	}
	if (GetWorldTimerManager().IsTimerActive(SkillCooldown_TimerHandle))
	{
		GetWorldTimerManager().ClearTimer(SkillCooldown_TimerHandle);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawRangeDecal();


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

