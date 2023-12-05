// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WC_CharacterBase.generated.h"

class USkeletalMeshComponent;

UCLASS()
class WIZARDCAVEV2_API AWC_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWC_CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Returns Mesh1P subobject
	USkeletalMeshComponent* GetCharMesh() const { return CharMesh; }

	// fire magic projectile
	virtual void ShootMagic();

protected:
	// pawn mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* CharMesh;

	// location where magic projectile spawns
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	// magic projectile class
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TSubclassOf<class AMagicProjectile> ProjectileClass;

	// mana cost for using magic projectile
	UPROPERTY(EditAnywhere)
	float FireballManaCost = 10.f;
};
