// Fill out your copyright notice in the Description page of Project Settings.


#include "LootComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
ULootComponent::ULootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULootComponent::DropLoot()
{
	ChooseRandomLoot();
	
	// loot item must be set before continuing
	if(LootItem == nullptr) { return; }
	
	FVector Location = GetOwner()->GetActorLocation();
	FRotator Rotation = GetOwner()->GetActorRotation();

	// spawn loot at owning actors location - create offset?
	auto Loot = GetWorld()->SpawnActor<AActor>(LootItem, GetOwner()->GetActorTransform());

	Loot->SetActorLocation(DropToFloor());
}

void ULootComponent::ChooseRandomLoot()
{
	// random item array must have items in it
	if (RandomLootArray.IsEmpty()) { return; }

	// chooses random item index based on size of item array and sets loot item
	int32 RandomItemIndex = FMath::RandRange(0, (RandomLootArray.Num() - 1));
	LootItem = RandomLootArray[RandomItemIndex];
}

FVector ULootComponent::DropToFloor()
{
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start + GetOwner()->GetActorUpVector() * (-500);

	// line trace to the ground/first obstacle
	FHitResult OutHitResult;
	GetWorld()->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility);

	// returns ground location for loot placement
	return OutHitResult.Location;
}

