// copyright @����

#pragma once

#include "ForestMagus.h"
#include "Structs/Character/BaseCharacter.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "PlayerCharacter.generated.h"

class UFMAttributeSet;

UCLASS()
class FORESTMAGUS_API APlayerCharacter : public ABaseCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	APlayerCharacter();

protected:
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public : 
	//�����Ƽ �ý���
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();

	virtual void PossessedBy(AController* NewController)override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class UFMGameplayAbility>> DefaultAbilities;

	// ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	// ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class UStaticMeshComponent* WeaponMesh;

	// �ִϸ��̼�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerCharacterAnimInstance* PlayerAnim;

	// �ڷ���Ʈ - �������Ʈ �Լ� ����
	UFUNCTION(BlueprintImplementableEvent,Category = Teleportation)
	void Teleportation();

protected : 
	// �����Ƽ �ý���
	UPROPERTY()
	class UFMAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UFMAttributeSet* Attributes;

};
