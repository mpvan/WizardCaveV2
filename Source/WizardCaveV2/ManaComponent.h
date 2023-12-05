// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WIZARDCAVEV2_API UManaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UManaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// returns percentage of remaining mana for progress bar
	UFUNCTION(BlueprintPure)
	float GetManaPercent() const;

	// returns the amount of mana remaining
	UFUNCTION(BlueprintPure)
	float GetMana() const;

	// lowers mana by specified amount
	UFUNCTION()
	void DecreaseMana(float DecreaseAmount);

	// increases mana by specified amount
	UFUNCTION()
	void RestoreMana(float RestoreValue);

private:
	// maximum mana value
	UPROPERTY(EditAnywhere)
	float MaxMana = 100.f;
	// current mana value
	float Mana;
};
