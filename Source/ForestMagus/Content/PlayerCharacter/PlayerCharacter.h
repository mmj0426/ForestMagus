// copyright @민지

#pragma once

#include "ForestMagus.h"
#include "Structs/Abilities/FMAbilityInputIDEnum.h"
#include "Structs/Character/BaseCharacter.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerCharacterAnimInstance* PlayerAnim;

	// 텔레포트 - 블루프린트 함수 정의
	UFUNCTION(BlueprintImplementableEvent,Category = Teleportation)
	void Teleportation();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bCanShowCursorDecal;

	UFUNCTION(BlueprintCallable)
	void ShowDecal(bool CanShow);

	UFUNCTION(BlueprintCallable)
	void EndRangeSkill();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UFMGameplayAbility> BasicAttackAbility;

	// 스킬파편 획득 후 저장할 컨테이너
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EFMAbilityInputID, TSubclassOf<UFMGameplayAbility>> FragmentAbilities;

	// 스킬파편 획득 후 스킬 등록
	void SetAbility(TSubclassOf<UFMGameplayAbility> SkillAbility);

private : 
	// 마우스 커서 데칼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* RangeDecal;

	void OnSkillKeyPressed();
	void UseSkill_Pressed();
	void BasicAttack();

	EFMAbilityInputID CastingID;




};
