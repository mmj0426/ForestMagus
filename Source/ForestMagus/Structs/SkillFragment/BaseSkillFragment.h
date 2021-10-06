// copyright @¹ÎÁö

#pragma once

#include "ForestMagus.h"
#include "GameFramework/Actor.h"

#include "Structs/Abilities/FMGameplayAbility.h"

#include "BaseSkillFragment.generated.h"

UCLASS()
class FORESTMAGUS_API ABaseSkillFragment : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseSkillFragment();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION() 
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SkillFragmentMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UFMGameplayAbility> SkillAbility;

};
