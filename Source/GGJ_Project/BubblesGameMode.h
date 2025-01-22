// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BubblesGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GGJ_PROJECT_API ABubblesGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABubblesGameMode();
	
private:
	UPROPERTY(EditAnywhere, Category = Difficulty)
	int DifficultyLevel;

public:
	int GetDifficultyLevel() const;
	void IncrementDifficultyLevel();
};
