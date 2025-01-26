// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GGJ_Project/AI/BaseEnemyCharacter.h"


ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	//Mesh->SetSimulatePhysics(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 2000;
	ProjectileMovement->MaxSpeed = 3000;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletBeginOverlap);
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Lifespan increases 1 2 3 4 5 +++
	FVector Scale = GetActorScale3D();
	float NewScale = FMath::FInterpConstantTo(Scale.X, 0, DeltaTime, 1.f/ScalingInc);
	SetActorScale3D(FVector(NewScale));
}

void ABullet::SetDamage(float Value)
{
	Damage = Value;
}

void ABullet::OnBulletBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABaseEnemyCharacter* Enemy = Cast<ABaseEnemyCharacter>(OtherActor))
	{
		FDamageEvent DEvent;
		Enemy->TakeDamage(Damage, DEvent, GetWorld()->GetFirstPlayerController(), this);
	
		UE_LOG(LogTemp, Verbose, TEXT("Bot was hit for %f damage!"), Damage);
	}
	else
	{
		UE_LOG(LogTemp, Verbose, TEXT("Bullet hit a wall"));
	}
}

void ABullet::SetInitialVelocity(FVector& LaunchVelocity)
{
	ProjectileMovement->Velocity = LaunchVelocity * ProjectileMovement->InitialSpeed;
}

void ABullet::SetScalingToDeath(float Lifespan)
{
	SetLifeSpan(Lifespan);
	ScalingInc = Lifespan; 
}