// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "WizardCaveV2GameModeBase.h"
#include "LootComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// sets current health to maximum value at start
	Health = MaxHealth;

	// registers damage received function
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// true if health is 0
bool UHealthComponent::IsDead() const
{
	if (Health <= 0)
	{
		return true;
	}
	
	return false;
}

float UHealthComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void UHealthComponent::RestoreHealth(float RestoreValue)
{
	// restoration value should be positive
	if(RestoreValue <= 0.f) { return; }

	Health += RestoreValue;

	// current health value cannot exceed maximum health value
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	// damage value should be positive
	if(Damage <= 0.f) { return; }

	// cannot take additional damage if already dead
	if(Health <= 0.f) { return; }

	// damage value cannot exceed current health value
	Damage = FMath::Min(Health, Damage);
	Health -= Damage;

	//UE_LOG(LogTemp, Warning, TEXT("Current Health for %s: %f"), *GetOwner()->GetActorNameOrLabel(), Health);

	// damage sound effects
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DamageSound, DamagedActor->GetActorLocation());

	// handle death - TODO: refactor to own function
	if (IsDead())
	{
		class ACharacter* DeadCharacter = Cast<ACharacter>(DamagedActor);

		if (DeadCharacter)
		{
			DeadCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			AWizardCaveV2GameModeBase* GameMode = GetWorld()->GetAuthGameMode<AWizardCaveV2GameModeBase>();
			if (GameMode != nullptr)
			{
				// check behavior for killed pawn in current game mode
				GameMode->PawnKilled(DeadCharacter);
			}

			ULootComponent* LootComp = Cast<ULootComponent>(DeadCharacter->GetComponentByClass(ULootComponent::StaticClass()));
			if (LootComp != nullptr)
			{
				LootComp->DropLoot();
			}
			
			// remove controller and collision from dead character
			DeadCharacter->DetachFromControllerPendingDestroy();
			
		}
	}
}