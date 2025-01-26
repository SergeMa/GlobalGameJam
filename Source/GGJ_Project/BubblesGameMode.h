// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BubblesGameMode.generated.h"

class APickup;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnyPickupCollected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeToSpawnPickups);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDifficultyIncreased);

UCLASS()
class GGJ_PROJECT_API ABubblesGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABubblesGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	UAudioComponent* AudioComp;

private:
	UPROPERTY(EditAnywhere, Category = Difficulty)
	int DifficultyLevel;

	UPROPERTY(EditAnywhere, Category = Difficulty)
	int PlayerExperience;

	UPROPERTY(EditAnywhere, Category = Difficulty)
	int RequiredExperience;

	UPROPERTY(EditAnywhere, Category = Difficulty)
	int PlayerLevel;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* MainSoundtrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundWave* SoundLevelUp;

	UPROPERTY()
	FOnDifficultyIncreased OnDifficultyIncreased;
	
	UPROPERTY()
	FOnTimeToSpawnPickups OnTimeToSpawnPickups;

	UPROPERTY()
	FOnAnyPickupCollected OnAnyPickupCollected;
	
	int GetDifficultyLevel() const;
	void IncrementDifficultyLevel();
	void AddPlayerExperience(const int& Experience);
	void LevelUpPlayer();

	virtual void StartPlay();
};
