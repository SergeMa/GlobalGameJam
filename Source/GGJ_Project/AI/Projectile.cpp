


#include "GGJ_Project/AI/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GGJ_Project/PlayerPawn.h"
#include "Engine/DamageEvents.h"

AProjectile::AProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	/*Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);*/
	Mesh->SetSimulatePhysics(false);
	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 2000;
	ProjectileMovement->MaxSpeed = 3000;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;





}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA<APlayerPawn>()) {
	UE_LOG(LogTemp, Error, TEXT("HitProjectile"));
		APlayerPawn* Character = Cast<APlayerPawn>(OtherActor);
		if (!Character)return;
		FDamageEvent DEvent;
		OtherActor->TakeDamage(10, DEvent, Character->GetController(), this);
	}
		Destroy();
}

void AProjectile::SetInitialVelocity(FVector& LaunchVelocity)
{
	ProjectileMovement->Velocity = LaunchVelocity * ProjectileMovement->InitialSpeed;
}

