// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostSpeed.h"

#include "Components/AudioComponent.h"
#include "GGJ_Project/PlayerPawn.h"


ABoostSpeed::ABoostSpeed()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

void ABoostSpeed::BeginPlay()
{
	Super::BeginPlay();
	if (ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		GameMode->OnAnyPickupCollected.AddDynamic(this, &ABoostSpeed::HandleAnyPickup);
	}
}

void ABoostSpeed::Interact_Implementation(APlayerPawn* PlayerPawn)
{
	PlayerPawn->BoostSpeed(BoostTimer);
	if (ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		GameMode->AudioComp->Play(0);
		GameMode->OnAnyPickupCollected.Broadcast();
	}
}

void ABoostSpeed::HandleAnyPickup()
{
	Destroy();
}

