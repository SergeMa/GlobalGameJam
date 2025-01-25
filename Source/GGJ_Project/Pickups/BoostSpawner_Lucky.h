// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostSpawner_Lucky.generated.h"

class UPointLightComponent;
class APointLight;
class ABoostRanged;
class ABoostMelee;
class ABoostSpeed;
class ABoostHealth;
class APickup;

UCLASS()
class GGJ_PROJECT_API ABoostSpawner_Lucky : public AActor
{
	GENERATED_BODY()

public:
	ABoostSpawner_Lucky();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light)
	UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawner)
	TSubclassOf<ABoostHealth> BoostHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawner)
	TSubclassOf<ABoostSpeed> BoostSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawner)
	TSubclassOf<ABoostMelee> BoostMelee;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawner)
	TSubclassOf<ABoostRanged> BoostRanged;

	UFUNCTION()
	void OnTimeToSpawn();

protected:
	virtual void BeginPlay() override;
};
