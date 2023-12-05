// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class WIZARDCAVEV2_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	UTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// sets mover component associated with trigger area
	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);

private:
	// Tag of object used to make mover move
	UPROPERTY(EditAnywhere)
	FName UnlockTag;

	// linked mover compment
	UMover* Mover;

	// checks for item with correct tag to trigger movement
	AActor* GetAcceptableActor() const;
};
