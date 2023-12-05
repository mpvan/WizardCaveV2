// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "MagicProjectile.generated.h"

UCLASS()
class WIZARDCAVEV2_API AMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// magic projectile static mesh component
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ProjectileMesh;

	// length of time before projectile auto-destroys
	UPROPERTY(EditDefaultsOnly)
	float ProjectileLifespan = 3.f;

	// damage caused by magic projectile
	UPROPERTY(EditAnywhere)
	float ProjectileDamage = 10.f;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	// called when projectile hits another object
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// flame FX component
	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* FlameFX;

	// fireball sound cue
	UPROPERTY(EditAnywhere)
	USoundBase* FireballSound;
};
