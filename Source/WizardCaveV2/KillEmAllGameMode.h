// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WizardCaveV2GameModeBase.h"
#include "KillEmAllGameMode.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class WIZARDCAVEV2_API AKillEmAllGameMode : public AWizardCaveV2GameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	// called whenever a pawn is killed
	virtual void PawnKilled(APawn* PawnKilled) override;

	// returns number of enemies remaining in level
	UFUNCTION(BlueprintCallable)
	int32 GetEnemyCount();

private:
	// game over behavior
	void EndGame(bool bIsPlayerWinner);

	// UI widget class that appears at start of game, to be set in BP
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameStartHUDClass;

	// length of time UI widget remains on screen at start of game
	UPROPERTY(EditAnywhere)
	float StartHUDDisplayTime = 3.f;

	// timer handle for start game UI widget
	FTimerHandle StartHUDDisplayTimer;

	// start screen widget reference
	UUserWidget* StartScreen;

	// removes the UI widget at end of timer
	void ClearStartScreen();
};
