// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WizardCaveV2GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WIZARDCAVEV2_API AWizardCaveV2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled);
};
