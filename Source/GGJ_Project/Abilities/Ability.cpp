// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"

#include "Components/AudioComponent.h"
#include "GGJ_Project/PlayerPawn.h"


UAbility::UAbility()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UAbility::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerPawn>(GetOwner());
}

void UAbility::UpgradeAbility()
{
	Level += 1;
	Damage += DamageInc;
}

void UAbility::UseAbility() {}

