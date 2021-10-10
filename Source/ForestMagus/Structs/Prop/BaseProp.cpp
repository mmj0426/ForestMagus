
#include "Structs/Prop/BaseProp.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

ABaseProp::ABaseProp()
{
	PropMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PropMesh"));
	PropMesh->SetupAttachment(RootComponent);
}

void ABaseProp::BeginPlay()
{
	Super::BeginPlay();
}
