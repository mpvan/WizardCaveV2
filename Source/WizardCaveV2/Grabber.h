// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIZARDCAVEV2_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// pick up grabbable object in range
	UFUNCTION(BlueprintCallable)
	void Grab();

	// drop held object
	UFUNCTION(BlueprintCallable)
	void Release();

private:
	// how far the player can reach to grab
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400.f;

	// radius of sphere trace for grabbing
	UPROPERTY(EditAnywhere)
	float GrabRadius = 100.f;

	// how far from player grabbed item is held
	UPROPERTY(EditAnywhere)
	float HoldDistance = 200.f;

	// returns physics handle component
	UPhysicsHandleComponent* GetPhysicsHandle() const;

	// checks for grabbable items in range
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;
};
