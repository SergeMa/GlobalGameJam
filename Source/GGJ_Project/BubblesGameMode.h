// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BubblesGameMode.generated.h"

class APickup;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnyPickupCollected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeToSpawnPickups);

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
	int PlayerLevel;

	// TODO: delete later, test timer
	FTimerHandle TimerHandle;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* MainSoundtrack;

	UPROPERTY()
	FOnTimeToSpawnPickups OnTimeToSpawnPickups;

	UPROPERTY()
	FOnAnyPickupCollected OnAnyPickupCollected;
	
	int GetDifficultyLevel() const;
	void IncrementDifficultyLevel();
	void AddPlayerExperience(const int& Experience);

	virtual void StartPlay();
};
