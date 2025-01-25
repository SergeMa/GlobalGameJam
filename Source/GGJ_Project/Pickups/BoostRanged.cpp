// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostRanged.h"

#include "Components/AudioComponent.h"
#include "GGJ_Project/PlayerPawn.h"
#include "GGJ_Project/Abilities/PlayerAbilityComponent.h"
#include "GGJ_Project/Abilities/RangedShot.h"


// Sets default values
ABoostRanged::ABoostRanged()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

void ABoostRanged::BeginPlay()
{
	Super::BeginPlay();
	if (ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		GameMode->OnAnyPickupCollected.AddDynamic(this, &ABoostRanged::HandleAnyPickup);
	}
}

void ABoostRanged::Interact_Implementation(APlayerPawn* PlayerPawn)
{
	PlayerPawn->Abilities->RangedShot->UpgradeAbility();
	if (ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		GameMode->AudioComp->Play(0);
		GameMode->OnAnyPickupCollected.Broadcast();
	}
}

void ABoostRanged::HandleAnyPickup()
{
	Destroy();
}
