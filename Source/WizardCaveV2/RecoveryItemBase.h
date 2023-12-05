// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RecoveryItemBase.generated.h"

UCLASS()
class WIZARDCAVEV2_API ARecoveryItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARecoveryItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult& SweepResult);

	// returns the healing strength of the recovery item
	UFUNCTION(BlueprintPure)
	float GetRecoveryStrength() const;

private:
	// recovery item static mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemMesh;

	// particle system FX component
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ItemFX;

	// sound FX
	UPROPERTY(EditAnywhere)
	USoundBase* PickUpSFX;

protected:
	// overlap trigger area
	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerArea;

	// healing strength of recovery item
	UPROPERTY(EditAnywhere)
	float RecoveryStrength = 10.f;
};
