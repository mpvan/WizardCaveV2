// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "CameraCauldron.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystemComponent;

UCLASS()
class WIZARDCAVEV2_API ACameraCauldron : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraCauldron();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// potion trigger overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult& SweepResult);

private:
	// cauldron mesh
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* CauldronMesh;

	// overlap trigger for potion
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* PotionTrigger;

	// cauldron flame fx
	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* CauldronFX;
};