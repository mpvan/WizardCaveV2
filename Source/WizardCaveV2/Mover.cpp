// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// store location of owner actor at start of game
	OriginalLocation = GetOwner()->GetActorLocation();	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// when true, moves owner actor to target location according to offset variable and speed
	if (ShouldMove)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OriginalLocation + MoveOffset;
		float Speed = FVector::Distance(OriginalLocation, TargetLocation) / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

		GetOwner()->SetActorLocation(NewLocation);

		if (WallSound != nullptr)
		{
			// plays sfx for wall movement
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), WallSound, GetOwner()->GetActorLocation());
		}
	}
}

// changes bool which activates mover component
void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}