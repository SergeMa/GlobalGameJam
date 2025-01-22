// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability_Swipe.h"

#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UAbility_Swipe::UAbility_Swipe()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UAbility_Swipe::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAbility_Swipe::AcquireAbility_Implementation()
{
	Level = 1;
	Damage = 10;
	Range = 200;
	Cooldown = 3;

	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UAbility_Swipe::UseAbility_Implementation, Cooldown, true, false);
}

void UAbility_Swipe::UpgradeAbility_Implementation()
{
	Level += 1;
	Damage += 10;
	Range *= 1.1;
	Cooldown *= 0.9;
}

void UAbility_Swipe::UseAbility_Implementation()
{
	FVector Location = GetOwner()->GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	TArray<FHitResult> Hits;
	UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		Location,
		Location,
		Range,
		ObjectTypes,
		false,
		{},
		EDrawDebugTrace::ForOneFrame,
		Hits,
		true);

	for(FHitResult Hit : Hits)
	{
		FDamageEvent DamageEvent;
		Hit.GetActor()->TakeDamage(Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), GetOwner());

		UE_LOG(LogTemp, Display, TEXT("Actor was hit for %f damage!"), Damage);
	}
}
