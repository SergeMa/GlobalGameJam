// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ABaseEnemyCharacter;

UCLASS()
class GGJ_PROJECT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	int DifficultyLevel;
	UPROPERTY(VisibleAnywhere)
	int EnemiesToSpawn;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawner)
	int MinSpawnCount = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawner)
	int LevelMultiplier = 25;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawner)
	float SpawnRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawner)
	TSubclassOf<ABaseEnemyCharacter> EnemyType;
	
public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

public:
	
	FTimerHandle SpawnTimer;

	UFUNCTION()
	void SpawnEnemy();
	
};
