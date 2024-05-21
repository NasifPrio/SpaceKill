// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceKillPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void ASpaceKillPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}

void ASpaceKillPlayerController::RestartCurrentLvel()
{
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void ASpaceKillPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	UE_LOG(LogTemp, Warning, TEXT("Game Over!"));

	HUD->RemoveFromViewport();

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
			GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = true;
			WinScreen->AddToViewport();
		}

	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
			GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = true;
			LoseScreen->AddToViewport();
		}
	}

}

