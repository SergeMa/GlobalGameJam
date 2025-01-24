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
	Damage += DamageInc;
}

void UAbility::UseAbility() {}

