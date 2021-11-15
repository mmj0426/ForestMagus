// Copyright @¹ÎÁö


#include "Content/GameMode/DungeonGameMode.h"

#include "GameFramework/HUD.h"

#include "Content/PlayerCharacter/PlayerCharacter.h"
#include "Content/PlayerCharacter/PlayerCharacterController.h"

ADungeonGameMode::ADungeonGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerCharacter>
	PlayerCharacter(TEXT("/Game/Characters/PlayerCharacter/BP_PlayerCharacter.BP_PlayerCharacter_C"));

	DefaultPawnClass = PlayerCharacter.Class;

	PlayerControllerClass = APlayerCharacterController::StaticClass();

	static ConstructorHelpers::FClassFinder<AHUD>
	HUD_Default(TEXT("/Game/Blueprint/HUD/Dungeon_HUD.Dungeon_HUD_C"));

	HUDClass = HUD_Default.Class;
}