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

	MaxHeight = GetActorLocation().Z+500.f;
	MinHeight = GetActorLocation().Z+100.f;
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
		Offset = FMath::Lerp(Location.Z, Location.Z + 200, DeltaTime);
		if(Location.Z > MaxHeight)
			bShouldGoUp = false;
	}
	else
	{
		Offset = FMath::Lerp(Location.Z, Location.Z - 200, DeltaTime);
		if(Location.Z < MinHeight)
			bShouldGoUp = true;
	}
	FVector NewLocation = FVector(Location.X, Location.Y, Offset);
	SetActorLocation(NewLocation);

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(14, 5.f, FColor::Red, FString::Printf(TEXT("ShouldGoUp: %i, max: %g, min: %g, curr: %g"), bShouldGoUp, MaxHeight, MinHeight, NewLocation.Z));
	}
}
