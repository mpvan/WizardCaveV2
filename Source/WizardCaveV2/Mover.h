// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIZARDCAVEV2_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// changes bool which activates mover component
	void SetShouldMove(bool ShouldMove);

private:
	// how far movement component should move
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	// amount of time to move to target
	UPROPERTY(EditAnywhere)
	float MoveTime = 4;

	// activate mover
	UPROPERTY(EditAnywhere)
	bool ShouldMove = false;

	// owner actor location at start of game
	FVector OriginalLocation;

	// wall movement sfx
	UPROPERTY(EditAnywhere)
	USoundBase* WallSound;
};
