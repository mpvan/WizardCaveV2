// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoveryItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
ARecoveryItemBase::ARecoveryItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// creates static mesh component
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	SetRootComponent(ItemMesh);

	// creates overlap trigger area component
	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Trigger"));
	TriggerArea->SetupAttachment(RootComponent);
	TriggerArea->SetBoxExtent(FVector(25.f, 25.f, 25.f));

	// creates particle system component
	ItemFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Item FX"));
	ItemFX->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARecoveryItemBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARecoveryItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARecoveryItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (OtherActor == Player)
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), PickUpSFX, GetActorLocation(), GetActorRotation());
	}
}

float ARecoveryItemBase::GetRecoveryStrength() const
{
	return RecoveryStrength;
}

