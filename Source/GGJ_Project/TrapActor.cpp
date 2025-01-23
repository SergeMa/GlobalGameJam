// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapActor.h"
#include "Components\StaticMeshComponent.h"
#include "Components\BoxComponent.h"
#include "TimerManager.h"
#include "PlayerPawn.h"

// Sets default values
ATrapActor::ATrapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TrapActivationArea = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivationArea"));
	RootComponent = TrapActivationArea;

	TrapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trap"));
	TrapMesh->SetupAttachment(TrapActivationArea);
}

// Called when the game starts or when spawned
void ATrapActor::BeginPlay()
{
	Super::BeginPlay();

    TrapActivationArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
    TrapMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);

    TrapMesh->SetGenerateOverlapEvents(true);
	TrapMesh->OnComponentBeginOverlap.AddDynamic(this, &ATrapActor::OnMeshOverlap);
	TrapActivationArea->OnComponentBeginOverlap.AddDynamic(this, &ATrapActor::OnMeshOverlap);

    MeshLowerLocation = TrapMesh->GetRelativeLocation();
	MeshUpperLocation = TrapMesh->GetRelativeLocation() + FVector(0, 0, TravelUpDistance);
}

// Called every frame
void ATrapActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (IsActivated)
    {
        FVector NewLocation = FMath::VInterpConstantTo(TrapMesh->GetRelativeLocation(), MeshUpperLocation, DeltaTime, TravelUpSpeed);
        TrapMesh->SetRelativeLocation(NewLocation);
    }
    else
    {
        FVector NewLocation = FMath::VInterpConstantTo(MeshLowerLocation, TrapMesh->GetRelativeLocation(), DeltaTime, TravelDownSpeed);
        TrapMesh->SetRelativeLocation(NewLocation);
    }
}

void ATrapActor::ResetActivationState()
{
    IsActivated = false;

    // Optionally, move the mesh back to its initial location
    TrapMesh->SetRelativeLocation(MeshLowerLocation);
    TrapVictims.Empty();    
    UE_LOG(LogTemp, Warning, TEXT("Trap Reset"));
}

void ATrapActor::TrapEffect_Implementation(ACharacter* Victim)
{

}

void ATrapActor::Interact_Implementation(APlayerPawn* PlayerPawn)
{
    if (IsActivated) return;

    UE_LOG(LogTemp, Warning, TEXT("TrapActivated"));
    IsActivated = true;
    GetWorld()->GetTimerManager().SetTimer(ActivationTimerHandle, this, &ATrapActor::ResetActivationState, ActivationCooldownSeconds, false);
}

void ATrapActor::OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsActivated) return;

    if (TriggerOnlyOnPlayer)
    {
        if (APlayerPawn* Player = Cast<APlayerPawn>(OtherActor))
        {
            if (!TrapVictims.Contains(Player))
            {
                TrapVictims.Add(Player);
                TrapEffect(Player);
            }
        }
    }
    else
    {
        if (ACharacter* Character = Cast<ACharacter>(OtherActor))
        {
            if (!TrapVictims.Contains(Character))
            {
                TrapVictims.Add(Character);
                TrapEffect(Character);
            }
        }
    }
}

