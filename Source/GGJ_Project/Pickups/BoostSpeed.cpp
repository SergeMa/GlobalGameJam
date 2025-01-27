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
}

void ABoostSpeed::Interact_Implementation(APlayerPawn* PlayerPawn)
{
	PlayerPawn->BoostSpeed(BoostTimer);
	Destroy();
}
