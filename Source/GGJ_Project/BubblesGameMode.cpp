// Fill out your copyright notice in the Description page of Project Settings.


#include "BubblesGameMode.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

ABubblesGameMode::ABubblesGameMode() : DifficultyLevel(0), PlayerExperience(0), PlayerLevel(0)
{
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
}

int ABubblesGameMode::GetDifficultyLevel() const { return DifficultyLevel; }

void ABubblesGameMode::IncrementDifficultyLevel() { DifficultyLevel++; }

void ABubblesGameMode::AddPlayerExperience(const int& Experience)
{

	UE_LOG(LogTemp, Display, TEXT("Experience gained: %d. Player level: %d"), Experience, PlayerLevel);
	
	PlayerExperience += Experience;
	const int LevelUp = PlayerExperience / 1000 - PlayerLevel;
	if (PlayerLevel < PlayerLevel + LevelUp)	
	{
		PlayerLevel += LevelUp;
		OnTimeToSpawnPickups.Broadcast();
		UE_LOG(LogTemp, Display, TEXT("OnTimeToSpawnPickups.Broadcast()"));
	}
}

void ABubblesGameMode::StartPlay()
{
	Super::StartPlay();
	UGameplayStatics::PlaySound2D(GetWorld(), MainSoundtrack, 1.0f);
}
