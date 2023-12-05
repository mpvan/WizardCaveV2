// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RecoveryItemBase.h"
#include "RecoveryItem_HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class WIZARDCAVEV2_API ARecoveryItem_HealthPotion : public ARecoveryItemBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult& SweepResult) override;
};
