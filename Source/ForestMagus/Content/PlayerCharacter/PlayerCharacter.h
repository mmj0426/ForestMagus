// copyright @����
// 
// edit 2021-10-15 @Winter
// DrawRangeDecal �Լ� �߰�
// GetCorsshairHitResult �߰�

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
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController)override;

public:
	// ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* StaffMesh;

	// �ִϸ��̼�
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//class UPlayerCharacterAnimInstance* PlayerAnim;

	// �ڷ���Ʈ - �������Ʈ �Լ� ����
	UFUNCTION(BlueprintImplementableEvent,Category = Teleportation)
	void Teleportation();

	// ������ ��ų ���� ��Į
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bCanShowCursorDecal;

	// �⺻ ���� �����Ƽ
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UFMGameplayAbility> BasicAttackAbility;

	// ��ų���� ȹ�� �� ������ �����̳�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<EFMAbilityInputID, TSubclassOf<UFMGameplayAbility>> FragmentAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFMPlayerState CurrentState;

public : 
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	// ������ ��ų 
	UFUNCTION(BlueprintCallable)
	void ShowDecal(bool CanShow);

	UFUNCTION(BlueprintCallable)
	void EndRangeSkill();

	void DrawRangeDecal();

	// Crosshair ����
	UFUNCTION(BlueprintCallable)
	bool GetCrosshairHitResult(FHitResult& Result);

	// ��ų���� ȹ�� �� ��ų ���
	void SetAbility(TSubclassOf<UFMGameplayAbility> SkillAbility, UTexture2D* SkillIcon);

public : 

	// �ൿ ���� (����)
	bool CanGetSkillFragment();

	bool CanMove() const;

	UFUNCTION(BlueprintCallable)
	bool CanTeleportation() const;

private : 
	// ���콺 Ŀ�� ��Į
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

};
