// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSwapper.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UCameraSwapper::UCameraSwapper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCameraSwapper::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UCameraSwapper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCameraSwapper::SwapCamera()
{
	PC = UGameplayStatics::GetPlayerController(this, 0);

	if (PC)
	{
		if (PortalCamera)
		{
			// swap to linked camera and start timer
			PC->SetViewTarget(PortalCamera);
			PC->GetWorldTimerManager().SetTimer(SwapTimer, this, &UCameraSwapper::ReturnViewToPlayer, TimeToCameraChange);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Camera Set!"));
		}
	}
}

void UCameraSwapper::ReturnViewToPlayer()
{
	PC = UGameplayStatics::GetPlayerController(this, 0);

	if (PC)
	{
		// return camera view to the player's camera
		PC->SetViewTarget(PC->GetPawn());
	}
}

