// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedShot.h"

#include "Bullet.h"
#include "Engine/DamageEvents.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GGJ_Project/PlayerPawn.h"
#include "GGJ_Project/AI/Projectile.h"
#include "Kismet/KismetSystemLibrary.h"


URangedShot::URangedShot() : bIsShooting(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URangedShot::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerPawn>(GetOwner());
}


void URangedShot::UseAbility()
{
	if (bIsShooting)
	{
		// Don't start new shot until animation ends
		UE_LOG(LogTemp, Verbose, TEXT("Ranged Shot on cooldown"));	
	}
	else
	{
		bIsShooting = true;
		if (Player)
		{
			Player->GetCharacterMovement()->SetMovementMode(MOVE_None);
			const float AnimLength = Player->PlayAnimMontage(ShotMontage, 0.5f);
			GetWorld()->GetTimerManager().SetTimer(ShotAnimTimer, this, &URangedShot::OnShotEnd, AnimLength*2, false);
		
			UE_LOG(LogTemp, Verbose, TEXT("Ranged Shot used"));
		}
	}

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Ranged Shot used"));
	}
}

void URangedShot::OnTriggerPulled()
{
	SpawnProjectile();
	UE_LOG(LogTemp, Verbose, TEXT("AnimNotify: trigger pulled"));
}

void URangedShot::OnShotEnd()
{
	bIsShooting = false;
	Player->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}


void URangedShot::SpawnProjectile()
{
	if (BulletClass)
	{
		FVector Location = Player->GetMesh()->GetSocketLocation("Barrel");
		FRotator Rotation = Player->GetActorRotation();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABullet* Projectile = GetWorld()->SpawnActor<ABullet>(BulletClass, Location, Rotation, SpawnParameters);
		if (Projectile)
		{
			Projectile->SetDamage(Damage);
			FVector LaunchDirection = Rotation.Vector();
			Projectile->SetInitialVelocity(LaunchDirection);
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(6, 5, FColor::Green, TEXT("Bullet spawned"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(6, 5, FColor::Red, TEXT("Bullet spawn failed"));
		}
	}
}
