// copyright @¹ÎÁö


#include "Content/HUD/TownHUD.h"

#include "Blueprint/UserWidget.h"

ATownHUD::ATownHUD()
{

}

void ATownHUD::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueWidget)
	{
		DialogueWidgetClass = CreateWidget<UUserWidget>(GetWorld(), DialogueWidget);
	}
}

UUserWidget* ATownHUD::GetDialogueWidget()
{
	return DialogueWidgetClass;
}
