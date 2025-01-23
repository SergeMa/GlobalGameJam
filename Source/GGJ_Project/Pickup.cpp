// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"

#include "BubblesGameMode.h"
#include "PlayerPawn.h"
#include "Abilities/MeleeStomp.h"
#include "Abilities/PlayerAbilityComponent.h"
#include "Abilities/RangedShot.h"
#include "GameFramework/CharacterMovementComponent.h"

class APlayerPawn;

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = PickupMesh;
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	if (ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		GameMode->OnAnyPickupCollected.AddDynamic(this, &APickup::HandleAnyPickup);
	}

	RandomBonus = FMath::RandRange(0, 3);
	UMaterialInstanceDynamic* Material = PickupMesh->CreateAndSetMaterialInstanceDynamic(0);
	FColor Color;
	
	switch (RandomBonus)
	{
	case 0:
		Color = FColor::Green;
		break;
	case 1:
		Color = FColor::Yellow;
		break;
	case 2:
		Color = FColor::Red;
		break;
	case 3:
		Color = FColor::Blue;
		break;
	default:
		Color = FColor::White;
	}
	
	Material->SetVectorParameterValue(FName(TEXT("Color")), Color);
}

void APickup::Interact_Implementation(APlayerPawn* PlayerPawn)
{
	switch (RandomBonus)
	{
	case 0:
		PlayerPawn->MaxHealth += BonusHealth;
		PlayerPawn->CurrentHealth = FMath::Clamp(PlayerPawn->CurrentHealth + BonusHealing, 0, PlayerPawn->MaxHealth);
		break;
	case 1:
		PlayerPawn->GetCharacterMovement()->MaxWalkSpeed += BonusSpeed;
		break;
	case 2:
		PlayerPawn->Abilities->MeleeStomp->UpgradeAbility();
		break;
	case 3:
		PlayerPawn->Abilities->RangedShot->UpgradeAbility();
		break;
	default:
		break;
	}
	
	if (ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		GameMode->OnAnyPickupCollected.Broadcast();
	}
}

void APickup::HandleAnyPickup()
{
	Destroy();
}