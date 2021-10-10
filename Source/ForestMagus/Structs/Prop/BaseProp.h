// copyright @¹ÎÁö
#pragma once

#include "ForestMagus.h"
#include "Structs/Character/BaseCharacter.h"
#include "BaseProp.generated.h"

/**
 * 
 */
UCLASS()
class FORESTMAGUS_API ABaseProp : public ABaseCharacter
{
	GENERATED_BODY()

public : 
	ABaseProp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PropMesh;

protected:

	virtual void BeginPlay() override;

	/*UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/
	
};
