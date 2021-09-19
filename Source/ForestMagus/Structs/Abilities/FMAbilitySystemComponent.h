// copyright @민지 
// edit 2021-0909 @Winter :
// 생성자 및 GetAbilitySystemComponentFromActor 제작
// edit 2021-0917 @Winter:
// GetActiveAbilitesWithTags 제작

#pragma once

#include "ForestMagus.h"
#include "AbilitySystemComponent.h"
#include "FMAbilitySystemComponent.generated.h"

class UFMGameplayAbility;

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API UFMAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	//Actor Param의 어빌리티 시스템 컴포넌트를 반환한다.
	//AbilitySystemGlobals에 이미 구현된 함수.
	//FMAbilitySystemComponent로 Cast해서 Return하기 위한 함수이다.
	static UFMAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

	//현재 캐릭터에 등록된 스킬을 태그로 구분해서 찾는다.
	//반환은 ActiveAbilities에 Add해서 반환

	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<UFMGameplayAbility*>& ActiveAbilities);
};
