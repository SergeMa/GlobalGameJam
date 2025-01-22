// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAbilityComponent.h"

#include "Ability_Swipe.h"

UPlayerAbilityComponent::UPlayerAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	Ability_Swipe = CreateDefaultSubobject<UAbility_Swipe>(TEXT("Ability_Swipe"));
}


void UPlayerAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	Ability_Swipe->AcquireAbility_Implementation();
}
