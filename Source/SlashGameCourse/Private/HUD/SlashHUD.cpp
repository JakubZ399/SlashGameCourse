#include "HUD/SlashHUD.h"
#include "Blueprint/UserWidget.h"
#include "HUD/SlashOverlay.h"

/*void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();
}*/

void ASlashHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && SlashOverlayClass)
		{
			SlashOverlay = CreateWidget<USlashOverlay>(Controller, SlashOverlayClass);
			SlashOverlay->AddToViewport();
		}
	}
}
