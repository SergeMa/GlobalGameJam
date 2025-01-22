// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_Project/AI/BaseEnemyCharacter.h"
#include "Components\CapsuleComponent.h"

// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(50.f, 50.f);
	Health = 100;
	OnTakeAnyDamage.AddDynamic(this, &ABaseEnemyCharacter::HandleTakeAnyDamage);
}

// Called when the game starts or when spawned
void ABaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABaseEnemyCharacter::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	FMath::Clamp(Health-Damage, 0, MaxHealth);

	UE_LOG(LogTemp, Error, TEXT("TakeDamage"));
}


void ABaseEnemyCharacter::Attack()
{
	
}

void ABaseEnemyCharacter::OnDeath()
{
}