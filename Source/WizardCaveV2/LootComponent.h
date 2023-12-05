// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIZARDCAVEV2_API ULootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// spawns specified loot item after death
	UFUNCTION(BlueprintCallable)
	void DropLoot();

	// chooses random item from array of actors
	UFUNCTION(BlueprintCallable)
	void ChooseRandomLoot();
	
	// drops loot item to floor
	UFUNCTION(BlueprintCallable)
	FVector DropToFloor();

protected:
	// loot item to be spawned
	TSubclassOf<AActor> LootItem;

	// array of possible loot items
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> RandomLootArray;
};
