// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeStomp.h"

#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"


UMeleeStomp::UMeleeStomp()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMeleeStomp::BeginPlay()
{
	Super::BeginPlay();
	
}

void UMeleeStomp::UseAbility()
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
		EDrawDebugTrace::ForDuration,
		Hits,
		true);

	for(FHitResult Hit : Hits)
	{
		FDamageEvent DamageEvent;
		if (Hit.GetActor()) {
			Hit.GetActor()->TakeDamage(Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), GetOwner());
		}
		UE_LOG(LogTemp, Display, TEXT("Actor was hit for %f damage!"), Damage);
	}
}

void UMeleeStomp::UpgradeAbility()
{
	Super::UpgradeAbility();
	Range += RangeInc;
	Cooldown -= CooldownInc;
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UAbility::UseAbility, Cooldown, true, false);
}
