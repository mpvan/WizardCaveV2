// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "CameraSwapper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIZARDCAVEV2_API UCameraSwapper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraSwapper();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// switches view to linked camera
	void SwapCamera();

	// returns view to player camera
	void ReturnViewToPlayer();
	
private:
	// linked camera
	UPROPERTY(EditAnywhere)
	AActor* PortalCamera;

	// length of time before camera returns to player view
	UPROPERTY(EditAnywhere)
	float TimeToCameraChange = 10.f;

	// player controller reference
	APlayerController* PC;
	
	// camera swap timer handle
	FTimerHandle SwapTimer;
};
