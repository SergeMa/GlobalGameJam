// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "BaseEnemyCharacter.h"
#include "GGJ_Project/BubblesGameMode.h"

AEnemySpawner::AEnemySpawner() : DifficultyLevel(1)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		GameMode->OnDifficultyIncreased.AddDynamic(this, &AEnemySpawner::OnDifficultyIncreased);
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
			UE_LOG(LogTemp, Verbose, TEXT("Enemy spawned."));
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

void AEnemySpawner::OnDifficultyIncreased()
{
	SpawnRate = 320 / DifficultyLevel;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnEnemy, SpawnRate, true, false);
}

