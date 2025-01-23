// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = PickupMesh;
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
}

void APickup::Interact_Implementation()
{
	Destroy();
}