// copyright @민지

#pragma once

#include "ForestMagus.h"
#include "Structs/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FORESTMAGUS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	
	APlayerCharacter();

	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bCanShowCursorDecal;

private : 
	// 마우스 커서 데칼
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};
