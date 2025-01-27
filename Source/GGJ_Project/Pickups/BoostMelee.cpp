// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostMelee.h"

#include "Components/AudioComponent.h"
#include "GGJ_Project/PlayerPawn.h"
#include "GGJ_Project/Abilities/MeleeStomp.h"
#include "GGJ_Project/Abilities/PlayerAbilityComponent.h"

ABoostMelee::ABoostMelee()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

void ABoostMelee::BeginPlay()
{
	Super::BeginPlay();
}

void ABoostMelee::Interact_Implementation(APlayerPawn* PlayerPawn)
{
	PlayerPawn->Abilities->MeleeStomp->UpgradeAbility();
	Destroy();
}