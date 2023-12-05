// Fill out your copyright notice in the Description page of Project Settings.


#include "RecoveryItem_ManaPotion.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "ManaComponent.h"

void ARecoveryItem_ManaPotion::BeginPlay()
{
	Super::BeginPlay();

	// register overlap function
	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &ARecoveryItem_ManaPotion::OnOverlapBegin);
}

void ARecoveryItem_ManaPotion::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFroomSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFroomSweep, SweepResult);

	// should only react to player character
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (OtherActor == Player)
	{
		// call to player mana component
		UManaComponent* ManaComp = Cast<UManaComponent>(OtherActor->GetComponentByClass(UManaComponent::StaticClass()));
		if (ManaComp != nullptr)
		{
			// increase mana by specified amount
			ManaComp->RestoreMana(RecoveryStrength);

			// destroy recovery item
			Destroy();
		}
	}
}
