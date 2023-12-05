// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WC_CharacterBase.h"
#include "Enemy_Basic.generated.h"

/**
 * 
 */
UCLASS()
class WIZARDCAVEV2_API AEnemy_Basic : public AWC_CharacterBase
{
	GENERATED_BODY()
	
public:
	AEnemy_Basic();

	// TODO: Add enemy specific shoot function, update BTTask_Shoot
};
