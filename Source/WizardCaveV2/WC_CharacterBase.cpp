// Fill out your copyright notice in the Description page of Project Settings.


#include "WC_CharacterBase.h"
#include "MagicProjectile.h"
#include "ManaComponent.h"

// Sets default values
AWC_CharacterBase::AWC_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWC_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWC_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWC_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWC_CharacterBase::ShootMagic()
{
	// confirm existing mana component and enough mana exists to fire projectile
	UManaComponent* ManaComp = Cast<UManaComponent>(GetComponentByClass(UManaComponent::StaticClass()));
	if (ManaComp != nullptr && ManaComp->GetMana() >= FireballManaCost)
	{
		// reduce current mana
		ManaComp->DecreaseMana(FireballManaCost);

		// spawn projectile and set spawner as owner
		FVector PSPLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator PSPRotation = ProjectileSpawnPoint->GetComponentRotation();
		auto Projectile = GetWorld()->SpawnActor<AMagicProjectile>(ProjectileClass, PSPLocation, PSPRotation);
		Projectile->SetOwner(this);
	}
	else
	{
		// TODO: Create an error widget for out of mana
		UE_LOG(LogTemp, Warning, TEXT("More mana needed!"));
	}
}