// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostSpawner_Lucky.h"

#include "BoostHealth.h"
#include "BoostMelee.h"
#include "BoostRanged.h"
#include "BoostSpeed.h"
#include "Components/PointLightComponent.h"
#include "GGJ_Project/BubblesGameMode.h"


ABoostSpawner_Lucky::ABoostSpawner_Lucky()
{
	PrimaryActorTick.bCanEverTick = true;
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
}

void ABoostSpawner_Lucky::BeginPlay()
{
	Super::BeginPlay();
	ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>();
	if (GameMode)
	{
		GameMode->OnTimeToSpawnPickups.AddDynamic(this, &ABoostSpawner_Lucky::OnTimeToSpawn);
	}
}

void ABoostSpawner_Lucky::OnTimeToSpawn()
{
	if (BoostHealth && BoostMelee && BoostRanged && BoostSpeed)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Randomize booster
		const int Randomizer = FMath::RandRange(1, 4);
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Spawner randomized %i"), Randomizer));
		}
		AActor* BoosterSpawn;
		if (Randomizer == 1)
		{
			BoosterSpawn = GetWorld()->SpawnActor<AActor>(BoostHealth, GetActorLocation(), GetActorRotation(), SpawnParameters);
			PointLight->SetLightColor(FColor::Green);
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(10, 10.f, FColor::Orange, "Spawned pickups on time.");
			}
		}
		else if (Randomizer == 2)
		{
			BoosterSpawn = GetWorld()->SpawnActor<AActor>(BoostSpeed, GetActorLocation(), GetActorRotation(), SpawnParameters);
			PointLight->SetLightColor(FColor::Yellow);
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(10, 10.f, FColor::Orange, "Spawned pickups on time.");
			}
		}
		else if (Randomizer == 3)
		{
			BoosterSpawn = GetWorld()->SpawnActor<AActor>(BoostMelee, GetActorLocation(), GetActorRotation(), SpawnParameters);
			PointLight->SetLightColor(FColor::Red);
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(10, 10.f, FColor::Orange, "Spawned pickups on time.");
			}
		}
		else if (Randomizer == 4)
		{
			BoosterSpawn = GetWorld()->SpawnActor<AActor>(BoostRanged, GetActorLocation(), GetActorRotation(), SpawnParameters);
			PointLight->SetLightColor(FColor::Blue);
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(10, 10.f, FColor::Orange, "Spawned pickups on time.");
			}
		}
		else
		{
			PointLight->LightColor = FColor::Purple;
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(10, 10.f, FColor::Orange, "Failed to spawn pickups on time.");
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Booster types are missing."));
	}
}
