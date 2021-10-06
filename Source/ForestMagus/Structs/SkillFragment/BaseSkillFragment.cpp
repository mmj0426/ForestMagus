// copyright @����


#include "Structs/SkillFragment/BaseSkillFragment.h"

#include "Content/PlayerCharacter/PlayerCharacter.h"

#include "Components/SphereComponent.h"

ABaseSkillFragment::ABaseSkillFragment()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	RootComponent = SphereCollision;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
	SM_Sphere(TEXT("/Game/Blueprint/SkillFragment/SM_Fragment.SM_Fragment"));
	if (SM_Sphere.Succeeded())
	{
		SphereMesh->SetStaticMesh(SM_Sphere.Object);
		SphereMesh->SetupAttachment(RootComponent);
		SphereMesh->SetCollisionProfileName(TEXT("NoCollision"));
	}

}

void ABaseSkillFragment::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseSkillFragment::OnOverlapBegin);
	
}

void ABaseSkillFragment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseSkillFragment::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (nullptr != PlayerCharacter)
	{
		// Player -> SetAbility
		Destroy();
	}
}
