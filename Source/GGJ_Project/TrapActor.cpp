// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapActor.h"
#include "Components\StaticMeshComponent.h"
#include "Components\BoxComponent.h"
#include "TimerManager.h"

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

	// Bind overlap events

    TrapMesh->SetGenerateOverlapEvents(true);
	TrapMesh->OnComponentBeginOverlap.AddDynamic(this, &ATrapActor::OnMeshOverlap);

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

}

void ATrapActor::ResetActivationState()
{
    IsActivated = false;

    // Optionally, move the mesh back to its initial location
    TrapMesh->SetRelativeLocation(MeshUpperLocation - FVector(0, 0, TravelUpDistance));
}

void ATrapActor::Interact_Implementation()
{
    if (IsActivated) return;

    UE_LOG(LogTemp, Warning, TEXT("TrapActivated"));
    IsActivated = true;
    HasActivatedOnPlayer = false;
    GetWorld()->GetTimerManager().SetTimer(ActivationTimerHandle, this, &ATrapActor::ResetActivationState, ActivationCooldownSeconds, false);
}

void ATrapActor::OnMeshOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Trap mesh collided with %s"), *OtherActor->GetName());
}

