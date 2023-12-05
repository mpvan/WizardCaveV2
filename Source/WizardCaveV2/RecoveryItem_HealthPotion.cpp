// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoveryItem_HealthPotion.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"

void ARecoveryItem_HealthPotion::BeginPlay()
{
	Super::BeginPlay();

	// register overlap function
	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &ARecoveryItem_HealthPotion::OnOverlapBegin);
}

void ARecoveryItem_HealthPotion::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFroomSweep, SweepResult);

	// only reacts to player character
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (OtherActor == Player)
	{
		// call to player health component
		UHealthComponent* HealthComp = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));
		if (HealthComp != nullptr)
		{
			// increases player health by specified amount
			HealthComp->RestoreHealth(RecoveryStrength);

			// destroy recovery item
			Destroy();
		}
	}
}
