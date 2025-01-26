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
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Spawner)
	float SpawnRate = 320;

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

	UFUNCTION()
	void OnDifficultyIncreased();
};
