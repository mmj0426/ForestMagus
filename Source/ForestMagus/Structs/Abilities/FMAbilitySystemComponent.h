// copyright @���� 
// edit 2021-0909 @Winter :
// ������ �� GetAbilitySystemComponentFromActor ����

#pragma once

#include "ForestMagus.h"
#include "AbilitySystemComponent.h"
#include "FMAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UFMAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	//Actor Param�� �����Ƽ �ý��� ������Ʈ�� ��ȯ�Ѵ�.
	//AbilitySystemGlobals�� �̹� ������ �Լ�.
	//FMAbilitySystemComponent�� Cast�ؼ� Return�ϱ� ���� �Լ��̴�.
	static UFMAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);
};
