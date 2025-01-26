// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_Project/AI/BaseEnemyCharacter.h"

#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "GGJ_Project/PlayerPawn.h"
#include "GGJ_Project/BubblesGameMode.h"
#include "GGJ_Project/AI/BubbleAIController.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundBase.h"


// Sets default values
ABaseEnemyCharacter::ABaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(50.f, 50.f);
	Health = 100;
	OnTakeAnyDamage.AddDynamic(this, &ABaseEnemyCharacter::HandleTakeAnyDamage);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetSound(SoundDeath);
	AudioComponent->SetPaused(true);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; 
	AIControllerClass = ABubbleAIController::StaticClass(); 
	
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
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AActor* DmgSpawn = GetWorld()->SpawnActor<AActor>(DmgTextActorClass, GetActorLocation(), GetActorRotation(), SpawnParameters);
	
	Health = FMath::Clamp(Health-Damage, 0, MaxHealth);
	UE_LOG(LogTemp, Error, TEXT("%i"), Health);
	if (Health == 0) OnDeath();
}


void ABaseEnemyCharacter::Attack()
{
	
}

void ABaseEnemyCharacter::OnDeath()
{
	
	if (ABubblesGameMode* GameMode = GetWorld()->GetAuthGameMode<ABubblesGameMode>())
	{
		GameMode->AddPlayerExperience(Experience);
	}

	AudioComponent->SetPaused(false);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Niagara,
	GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundDeath, GetActorLocation());
	Destroy();
	UE_LOG(LogTemp, Error, TEXT("OnDeth"));

}