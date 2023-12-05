// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaComponent.h"

// Sets default values for this component's properties
UManaComponent::UManaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UManaComponent::BeginPlay()
{
	Super::BeginPlay();

	// sets current mana to max value at start of game
	Mana = MaxMana;
	
}


// Called every frame
void UManaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UManaComponent::GetManaPercent() const
{
	return Mana / MaxMana;
}

float UManaComponent::GetMana() const
{
	return Mana;
}

void UManaComponent::DecreaseMana(float DecreaseAmount)
{
	// amount mana is lowered should be positive
	if(DecreaseAmount <= 0.f) { return; }

	// amount mana is lowered cannot be greater than current mana
	DecreaseAmount = FMath::Min(Mana, DecreaseAmount);
	Mana -= DecreaseAmount;
}

void UManaComponent::RestoreMana(float RestoreValue)
{
	// amount mana is increased should be positive
	if (RestoreValue <= 0.f) { return; }

	Mana += RestoreValue;

	if (Mana > MaxMana)
	{
		// mana cannot be increased above the maximum value
		Mana = MaxMana;
	}
}

