// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "pacmanCloneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PACMANCLONE_API ApacmanCloneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int Score = 0;

	UFUNCTION()
	void AddScore(int ScoreToGive);
};
