#pragma once

#include "ForestMagus/ForestMagus.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public : 
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;


private : 

	// 플레이어 캐릭터
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Meta = (AllowprivateAccess = true))
	class APlayerCharacter* FMPlayer;

	// 키보드 W,A,S,D
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);

	// 마우스 회전
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
};
