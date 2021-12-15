// copyright @민지
// 
// edit 2021-10-15 @Winter
// DrawRangeDecal 함수 추가
// GetCorsshairHitResult 추가

#pragma once

#include "ForestMagus.h"
#include "Structs/Abilities/FMAbilityInputIDEnum.h"
#include "Structs/Character/BaseCharacter.h"
#include "Structs/Enum/EFMPlayerState.h"
#include "PlayerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FCustomInputDelegate, EFMAbilityInputID InputKey);

UCLASS()
class FORESTMAGUS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	FORCEINLINE class UDecalComponent* GetRangeDecal() { return RangeDecal; }

protected:
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndplayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController)override;

public:
	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	// 무기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* StaffMesh;

	// 애니메이션
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//class UPlayerCharacterAnimInstance* PlayerAnim;

	// 텔레포트 - 블루프린트 이벤트
	UFUNCTION(BlueprintImplementableEvent,Category = Teleportation)
	void Teleportation();

	// 범위형 스킬 관련 데칼
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bCanShowCursorDecal;

	// 기본 공격 어빌리티
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UFMGameplayAbility> BasicAttackAbility;

	// 스킬파편 획득 후 저장할 컨테이너
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EFMAbilityInputID, TSubclassOf<UFMGameplayAbility>> FragmentAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFMPlayerState CurrentState;

public : 
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	// 범위형 스킬 
	UFUNCTION(BlueprintCallable)
	void ShowDecal(bool CanShow);

	//UFUNCTION(BlueprintCallable)
	//void EndRangeSkill();

	void DrawRangeDecal();

	// Crosshair 레이
	UFUNCTION(BlueprintCallable)
	bool GetCrosshairHitResult(FHitResult& Result);

	// 스킬파편 획득 후 스킬 등록
	UFUNCTION(BlueprintCallable)
	void SetAbility(bool IsFixedSkill,TSubclassOf<UFMGameplayAbility> SkillAbility, UMaterial* SkillIcon);

	UFUNCTION(BlueprintImplementableEvent)
	void RecoverMana();

	UFUNCTION(BlueprintImplementableEvent)
	void SetCooldownRate();

	UFUNCTION(BlueprintImplementableEvent)
	void Death();

public : 

	// 행동 조건 (제약)
	bool CanGetSkillFragment() const;

	bool CanMove() const;

	UFUNCTION(BlueprintCallable)
	bool CanTeleportation() const;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	bool CanNPCInteraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsCooldown;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float Cooldown;

private : 
	// 마우스 커서 데칼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* RangeDecal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings/Crosshair", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> CrosshairObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings/Crosshair", meta = (AllowPrivateAccess = "true"))
	bool bCrosshairDebug;

	EFMAbilityInputID InputKey;
	EFMAbilityInputID CastingID;



private : 

	void OnSkillKeyPressed();
	void UseSkill_Pressed();
	void BasicAttack();

	void SeparateSkillKey(FKey key);

	// 타이머
	FTimerHandle RecoverMana_TimerHandle;
	FTimerHandle SkillCooldown_TimerHandle;

};
