// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_PlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "EnemyAIController.h"
#include "BrainComponent.h"
#include "EngineUtils.h"

void AWC_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// creates and displays player HUD UI widget at start of game
	PlayerHUD = CreateWidget(this, HUDClass);
	if (PlayerHUD)
	{
		PlayerHUD->AddToViewport();
	}
}

void AWC_PlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	// removes player HUD UI widget
	PlayerHUD->RemoveFromViewport();
	
	if (bIsWinner)
	{
		// creates and displays win screen UI widget if player is winner
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();
		}		
	}
	else
	{
		// creates and displays lose screen UI widget if player loses
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();
		}

		for (AEnemyAIController* AIController : TActorRange<AEnemyAIController>(GetWorld()))
		{
			AIController->GetBrainComponent()->StopLogic(TEXT("PlayerDead"));
		}
	}

	// starts game restart timer
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
