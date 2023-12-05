// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Basic.h"

AEnemy_Basic::AEnemy_Basic()
{
	// Create projectile spawn point
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Magic Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}
