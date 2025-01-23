// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "BaseEnemyCharacter.h"
#include "GGJ_Project/BubblesGameMode.h"

AEnemySpawner::AEnemySpawner() : DifficultyLevel(0), EnemiesToSpawn(MinSpawnCount)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (const ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		DifficultyLevel = GameMode->GetDifficultyLevel();
		EnemiesToSpawn = MinSpawnCount + DifficultyLevel * LevelMultiplier;
	}
	
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnEnemy, SpawnRate, true, false);
}

void AEnemySpawner::SpawnEnemy()
{
	if (EnemyType != nullptr)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* EnemySpawn = GetWorld()->SpawnActor<AActor>(EnemyType, GetActorLocation(), GetActorRotation(), SpawnParameters);
		if (EnemySpawn)
		{
			EnemiesToSpawn--;
			if (EnemiesToSpawn == 0)
			{
				GetWorldTimerManager().ClearTimer(SpawnTimer);
			}
			UE_LOG(LogTemp, Verbose, TEXT("Enemy spawned. Enemies to spawn: %d"), EnemiesToSpawn);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn enemy."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy type is not selected."));
	}
}

