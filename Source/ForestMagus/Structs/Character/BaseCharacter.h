#pragma once

#include "ForestMagus.h"
#include "GameFramework/Character.h"

#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>

#include "BaseCharacter.generated.h"

class UFMAttributeSet;
class UGameplayEffect;

UCLASS()
class FORESTMAGUS_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;

public:
	//어빌리티 시스템
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();

	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintCallable)
	virtual int GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable)
	virtual void ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<TSubclassOf<class UFMGameplayAbility>> DefaultAbilities;

	// Meteor Test
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UFMGameplayAbility>QSkillFragment;

protected:
	// 어빌리티 시스템

	/** 캐릭터의 레벨 (어빌리티 시스템에서 사용) */
	UPROPERTY(EditAnywhere, Category = Abilities)
	int CharacterLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UFMAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UFMAttributeSet* Attributes;
};
