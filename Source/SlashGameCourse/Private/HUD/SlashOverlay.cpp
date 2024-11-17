// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USlashOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void USlashOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void USlashOverlay::SetGold(int32 Gold)
{
	if (GoldCount)
	{
		const FString GoldString = FString::Printf(TEXT("%d"), Gold);
		const FText GoldText = FText::FromString(GoldString);
		GoldCount->SetText(GoldText);
	}
}

void USlashOverlay::SetSouls(int32 Souls)
{
	if (SoulsCount)
	{
		const FString SoulsString = FString::Printf(TEXT("%d"), Souls);
		const FText SoulsText = FText::FromString(SoulsString);
		SoulsCount->SetText(SoulsText);
	}
}
