
#include "Content/GameMode/TownGameMode.h"

#include "GameFramework/HUD.h"

#include "Content/PlayerCharacter/PlayerCharacter.h"
#include "Content/PlayerCharacter/PlayerCharacterController.h"

ATownGameMode::ATownGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerCharacter>
	PlayerCharacter (TEXT("/Game/Characters/PlayerCharacter/BP_PlayerCharacter.BP_PlayerCharacter_C"));

	DefaultPawnClass = PlayerCharacter.Class;
	
	PlayerControllerClass = APlayerCharacterController::StaticClass();

	static ConstructorHelpers::FClassFinder<AHUD>
	HUD_Default(TEXT("/Game/Blueprint/HUD/HUD_Crosshair.HUD_Crosshair_C"));

	HUDClass = HUD_Default.Class;
}