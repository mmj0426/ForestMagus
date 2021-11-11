// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "GameFramework/Character.h"
#include "BaseNPC.generated.h"

UCLASS()
class FORESTMAGUS_API ABaseNPC : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseNPC();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected : 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USphereComponent* DetectCollision;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
