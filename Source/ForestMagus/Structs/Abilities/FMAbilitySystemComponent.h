// copyright @민지 
// edit 2021-0909 @Winter :
// 생성자 및 GetAbilitySystemComponentFromActor 제작

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
	//Actor Param의 어빌리티 시스템 컴포넌트를 반환한다.
	//AbilitySystemGlobals에 이미 구현된 함수.
	//FMAbilitySystemComponent로 Cast해서 Return하기 위한 함수이다.
	static UFMAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);
};
