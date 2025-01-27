// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "BaseEnemyCharacter.h"
#include "GGJ_Project/BubblesGameMode.h"

AEnemySpawner::AEnemySpawner() : DifficultyLevel(0), EnemiesToSpawn(1), EnemiesSpawned(0)
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
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AActor* EnemySpawn = GetWorld()->SpawnActor<AActor>(EnemyType, GetActorLocation(), GetActorRotation(), SpawnParameters);
		if (EnemySpawn)
		{
			EnemiesSpawned++;
			EnemiesToSpawn--;
			if(EnemiesToSpawn < 1)
				GetWorldTimerManager().ClearTimer(SpawnTimer);
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
	DifficultyLevel++;
	EnemiesToSpawn = (FMath::Square(DifficultyLevel)+FMath::Square(DifficultyLevel+1));
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::SpawnEnemy, SpawnRate, true, false);
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Purple, FString::Printf(TEXT("EnemiesToSpawn: %d, difficulty level: %g"), EnemiesToSpawn, DifficultyLevel));
	}
}

