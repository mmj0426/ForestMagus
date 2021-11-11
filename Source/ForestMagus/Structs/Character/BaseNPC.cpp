// copyright @����


#include "Structs/Character/BaseNPC.h"

#include "Components/SphereComponent.h"

#include "Content/PlayerCharacter/PlayerCharacter.h"

ABaseNPC::ABaseNPC()
{
	PrimaryActorTick.bCanEverTick = true;

	DetectCollision = CreateDefaultSubobject<USphereComponent>(TEXT("DetectCollision"));
	DetectCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	DetectCollision->SetupAttachment(RootComponent);
}

void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();

	DetectCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseNPC::OnOverlapBegin);
	DetectCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseNPC::OnOverlapEnd);
	
}

void ABaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseNPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ��ȣ�ۿ� UI
	auto PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (nullptr != PlayerCharacter)
	{
		FMLOG(Warning, TEXT("Overlap Begin"));
		PlayerCharacter->CanNPCInteraction = true;
	}

	// ��ȭ
}

void ABaseNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// ��ȣ�ۿ� UI
	auto PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (nullptr != PlayerCharacter)
	{
		FMLOG(Warning, TEXT("Overlap End"));
		PlayerCharacter->CanNPCInteraction = false;
	}
}

