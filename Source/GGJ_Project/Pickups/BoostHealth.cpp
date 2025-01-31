﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostHealth.h"

#include "Components/AudioComponent.h"
#include "GGJ_Project/PlayerPawn.h"


ABoostHealth::ABoostHealth()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

void ABoostHealth::BeginPlay()
{
	Super::BeginPlay();
}

void ABoostHealth::Interact_Implementation(APlayerPawn* PlayerPawn)
{
	PlayerPawn->MaxHealth += BonusHealth;
	PlayerPawn->CurrentHealth = FMath::Clamp(PlayerPawn->CurrentHealth + BonusHealing, 0, PlayerPawn->MaxHealth);
	Destroy();
}