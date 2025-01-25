// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"

#include "Components/AudioComponent.h"
#include "GGJ_Project/BubblesGameMode.h"

class ABubblesGameMode;
class APlayerPawn;

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
}

void APickup::Interact_Implementation(APlayerPawn* PlayerPawn)
{
	if (ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		GameMode->OnAnyPickupCollected.Broadcast();
	}
}

void APickup::Tick(float DeltaTime)
{
	FVector Location = GetActorLocation();
	float Offset;
	if (bShouldGoUp)
	{
		Offset = FMath::Lerp(Location.Z, 600.f, DeltaTime);
		if(Location.Z > 400.f)
			bShouldGoUp = false;
	}
	else
	{
		Offset = FMath::Lerp(Location.Z, 0.f, DeltaTime);
		if(Location.Z < 100.f)
			bShouldGoUp = true;
	}
	FVector NewLocation = FVector(Location.X, Location.Y, Offset);
	SetActorLocation(NewLocation);
}
