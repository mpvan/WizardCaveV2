// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create static mesh component
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(ProjectileMesh);

	// create projectile movement component and setup movement defaults
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	// create particle system component for flame FX
	FlameFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Flame FX"));
	FlameFX->SetupAttachment(ProjectileMesh);

	// set projectile lifespan
	SetLifeSpan(ProjectileLifespan);
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	// register on hit function
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AMagicProjectile::OnHit);

	if (FireballSound != nullptr)
	{
		// play sound FX
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireballSound, GetActorLocation());
	}
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMagicProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) { return; }

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// apply projectile damage to hit actor
		UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, MyOwnerInstigator, this, DamageTypeClass);

		AActor* Player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (OtherActor == Player)
		{
			Destroy();
		}
	}

	// destroy projectile after hit
	// Destroy();
}