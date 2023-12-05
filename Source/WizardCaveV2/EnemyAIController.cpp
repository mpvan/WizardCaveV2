// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "WC_CharacterBase.h"
#include "HealthComponent.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		// start behavior tree
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		
		// sets the starting location of enemy pawn
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AEnemyAIController::IsDead() const
{
	AWC_CharacterBase* ControlledCharacter = Cast<AWC_CharacterBase>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		UHealthComponent* HealthComp = Cast<UHealthComponent>(ControlledCharacter->GetComponentByClass(UHealthComponent::StaticClass()));
		
		if (HealthComp != nullptr)
		{
			// check health component to learn if enemy has 0 health
			return HealthComp->IsDead();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Health Component not found!"));
		}
	}

	return true;
}
