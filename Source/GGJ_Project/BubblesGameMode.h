// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BubblesGameMode.generated.h"


class APickup;

UCLASS()
class GGJ_PROJECT_API ABubblesGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABubblesGameMode();
	
private:
	UPROPERTY(EditAnywhere, Category = Difficulty)
	int DifficultyLevel;

	UPROPERTY(EditAnywhere, Category = Difficulty)
	int PlayerExperience;

	UPROPERTY(EditAnywhere, Category = Difficulty)
	int PlayerLevel;

public:
	
	UPROPERTY(EditDefaultsOnly, Category = Level)
	TSubclassOf<APickup> PickupType;
	
	int GetDifficultyLevel() const;
	void IncrementDifficultyLevel();

	int GetPlayerLevel() const;
	void AddPlayerExperience(const int& Experience, const FVector& BotDeathLocation);
	
	void SpawnPickup(const FVector& Location) const;
};
