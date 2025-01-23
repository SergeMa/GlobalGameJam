// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"


UAbility::UAbility()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UAbility::BeginPlay()
{
	Super::BeginPlay();
}

void UAbility::UpgradeAbility()
{
	Level += 1;
	Damage *= DamageInc; 
	Range += RangeInc;
	Cooldown += CooldownInc;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UAbility::UseAbility, Cooldown, true, false);
}

void UAbility::UseAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("Ability is used! No definition."));
}


