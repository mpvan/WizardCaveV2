// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIZARDCAVEV2_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// checks if current health is 0
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// returns current health as a percent (for progress bar)
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// increases current health by specified value
	UFUNCTION()
	void RestoreHealth(float RestoreValue);

private:
	// maximum health value
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	// current health value
	UPROPERTY(VisibleAnywhere)
	float Health;

	// called when damage is taken by owning actor
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

	// damage sound fx
	UPROPERTY(EditAnywhere)
	USoundBase* DamageSound;
};
