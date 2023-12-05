// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraCauldron.h"
#include "Components/BoxComponent.h"
#include "CameraSwapper.h"

// Sets default values
ACameraCauldron::ACameraCauldron()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create static mesh component
	CauldronMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cauldron Mesh"));
	SetRootComponent(CauldronMesh);

	// Create potion trigger area component
	PotionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Potion Trigger Area"));
	PotionTrigger->SetupAttachment(CauldronMesh);
	PotionTrigger->InitBoxExtent(FVector(25.f, 25.f, 25.f));
	PotionTrigger->SetRelativeLocation(FVector(0.f, 0.f, 130.f));

	// create cauldron flame fx component
	CauldronFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Cauldron FX"));
	CauldronFX->SetupAttachment(PotionTrigger);
}

// Called when the game starts or when spawned
void ACameraCauldron::BeginPlay()
{
	Super::BeginPlay();

	// Register Overlap Event
	PotionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACameraCauldron::OnOverlapBegin);
}

// Called every frame
void ACameraCauldron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACameraCauldron::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->ActorHasTag("CameraPotion") && !OtherActor->ActorHasTag("Grabbed"))
		{
			UCameraSwapper* CamSwapComp = Cast<UCameraSwapper>(GetComponentByClass(UCameraSwapper::StaticClass()));

			// change view to linked camera for specified time, destroy potion
			if (CamSwapComp)
			{
				CamSwapComp->SwapCamera();
				OtherActor->Destroy();
			}
		}
	}
}
