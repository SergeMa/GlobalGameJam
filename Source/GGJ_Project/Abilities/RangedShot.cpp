// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedShot.h"

#include "Engine/DamageEvents.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
URangedShot::URangedShot()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void URangedShot::BeginPlay()
{
	Super::BeginPlay();
}


void URangedShot::UseAbility()
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
		if (Hit.GetActor()) {
			Hit.GetActor()->TakeDamage(Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), GetOwner());
		}
		UE_LOG(LogTemp, Display, TEXT("Actor was hit for %f damage!"), Damage);
	}
}

