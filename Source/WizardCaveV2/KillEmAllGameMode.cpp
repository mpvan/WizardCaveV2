// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "EnemyAIController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AKillEmAllGameMode::BeginPlay()
{
	Super::BeginPlay();

	StartScreen = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameStartHUDClass);
	if (StartScreen)
	{
		// displays start screen UI widget and starts display timer
		StartScreen->AddToViewport();
		GetWorldTimerManager().SetTimer(StartHUDDisplayTimer, this, &AKillEmAllGameMode::ClearStartScreen, StartHUDDisplayTime);
	}
}

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

	if (PlayerController != nullptr)
	{
		// pawn killed has player controller - game over
		EndGame(false);
	}

	// loop over all enemy AI controllers in level
	for (AEnemyAIController* AIController : TActorRange<AEnemyAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			// game does not end if living enemy AI found
			return;
		}
	}

	// no living enemy AI found after loop
	EndGame(true);
}

int32 AKillEmAllGameMode::GetEnemyCount()
{
	int32 EnemyCount = 0;

	// loop over all enemy AI controllers in level
	for (AEnemyAIController* AIController : TActorRange<AEnemyAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			// game does not end if living enemy AI found
			EnemyCount++;
		}
	}

	return EnemyCount;
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	// loop over all controllers in level
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// determines winner based on remaining controller(s)
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;

		// ends the game
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}

void AKillEmAllGameMode::ClearStartScreen()
{
	// clears start screen UI widget
	StartScreen->RemoveFromViewport();
}
