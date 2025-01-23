// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAbilityComponent.h"

#include "MeleeStomp.h"
#include "RangedShot.h"

UPlayerAbilityComponent::UPlayerAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	MeleeStomp = CreateDefaultSubobject<UMeleeStomp>(TEXT("MeleeStomp"));
	RangedShot = CreateDefaultSubobject<URangedShot>(TEXT("RangedShot"));
}

void UPlayerAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}
