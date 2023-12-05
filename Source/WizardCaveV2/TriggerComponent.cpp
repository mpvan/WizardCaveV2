// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Mover == nullptr) { return; }

	// check that player is holding actor with correct unlock tag
	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		UPrimitiveComponent* Comp = Cast<UPrimitiveComponent> (Actor->GetRootComponent());
		if (Comp != nullptr)
		{
			// turn physics off for key
			Comp->SetSimulatePhysics(false);
		}

		// key item attaches to trigger component
		Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		// activate mover component
		Mover->SetShouldMove(true);
	}
	else
	{
		// mover component is not activated if object does not have correct unlock tag
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	// create array of all actors overlapping trigger area
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		bool HasAcceptableTag = Actor->ActorHasTag(UnlockTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");

		// return actor if it has matching unlock tag and has been released by player
		if (HasAcceptableTag && !(IsGrabbed))
		{
			return Actor;
		}
	}

	// null pointer if unlock tag does not match
	return nullptr;
}