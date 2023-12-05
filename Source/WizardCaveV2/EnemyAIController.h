// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class WIZARDCAVEV2_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds);

	// returns true if health is 0
	bool IsDead() const;

private:
	// AI behavior tree
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
};
