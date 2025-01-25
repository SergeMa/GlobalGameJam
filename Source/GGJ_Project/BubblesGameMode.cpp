// Fill out your copyright notice in the Description page of Project Settings.


#include "BubblesGameMode.h"

#include "Pickup.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

ABubblesGameMode::ABubblesGameMode() : DifficultyLevel(0), PlayerExperience(0), PlayerLevel(0) {}

int ABubblesGameMode::GetDifficultyLevel() const { return DifficultyLevel; }

void ABubblesGameMode::IncrementDifficultyLevel() { DifficultyLevel++; }

int ABubblesGameMode::GetPlayerLevel() const { return PlayerExperience % 100; }

void ABubblesGameMode::AddPlayerExperience(const int& Experience, const FVector& BotDeathLocation)
{

	UE_LOG(LogTemp, Display, TEXT("Experience gained: %d. Player level: %d"), Experience, PlayerLevel);
	
	PlayerExperience += Experience;
	const int LevelUp = PlayerExperience / 1000 - PlayerLevel;
	if (PlayerLevel < PlayerLevel + LevelUp)	
	{
		PlayerLevel = PlayerLevel + LevelUp;
		SpawnPickup(FVector(BotDeathLocation.X, BotDeathLocation.Y - 200, BotDeathLocation.Z));
		SpawnPickup(FVector(BotDeathLocation.X, BotDeathLocation.Y + 200, BotDeathLocation.Z));
	}
}
void ABubblesGameMode::SpawnPickup(const FVector& Location) const
{
	if (PickupType != nullptr)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* PickupSpawn = GetWorld()->SpawnActor<AActor>(PickupType, Location, FRotator::ZeroRotator, SpawnParameters);
		if (PickupSpawn)
		{
			UE_LOG(LogTemp, Verbose, TEXT("Pickup spawned."));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn a pickup."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pickup type is not selected."));
	}
}

void ABubblesGameMode::StartPlay()
{
	Super::StartPlay();
	UGameplayStatics::PlaySound2D(GetWorld(), MainSoundtrack, 1.0f);
}
