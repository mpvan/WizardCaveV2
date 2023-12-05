// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WC_PlayerController.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class WIZARDCAVEV2_API AWC_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	// player HUD widget class
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;
	
	// losing game over widget class
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreenClass;

	// winning game over widget class
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;
	
	// length of time after game over before game restarts
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	// timer handle for game restart after game over
	FTimerHandle RestartTimer;

	// player HUD widget reference
	UPROPERTY()
	UUserWidget* PlayerHUD;
};
