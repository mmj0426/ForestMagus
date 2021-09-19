// copyright @����

#pragma once

#include "ForestMagus.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "FMAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class FORESTMAGUS_API UFMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public : 

	UFMAttributeSet();

	/* Attribue�� �ٲ������ ȣ��Ǵ� �̺�Ʈ�Լ� **/
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	/** GaemplayEffect�� ����ȵ� ȣ��Ǵ� �̺�Ʈ �Լ� */
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UFMAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UFMAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UFMAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UFMAttributeSet, MaxMana)

	/**
	* Damage�� �Ͻ������� ���Ǵ� Attribue
	* DamageExecution���� ���Ǵ� �������� �����Ѵ�.
	* ����� ��������ŭ Health�� ���ҽ�Ŵ
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UFMAttributeSet, Damage)

protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
};
