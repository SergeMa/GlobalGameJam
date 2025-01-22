// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Components\StaticMeshComponent.h"
#include "Components\BoxComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

void APickup::Interact_Implementation()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Green, "APickup Interact");
	}
	Destroy();
}

