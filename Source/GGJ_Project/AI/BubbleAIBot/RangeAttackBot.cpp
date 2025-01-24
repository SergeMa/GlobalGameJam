// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_Project/AI/BubbleAIBot/RangeAttackBot.h"
#include "GGJ_Project/AI/BubbleAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GGJ_Project/AI/Projectile.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

ARangeAttackBot::ARangeAttackBot()
{
}



void ARangeAttackBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckDistance())
		StartAttack();
	else
		StopAttack();

}

bool ARangeAttackBot::CheckDistance()
{
	auto BubbleController = Cast<ABubbleAIController>(GetController());
	if (!BubbleController)return false;

	AActor* CurrentActor = BubbleController->GetcurentActor();
	if (!CurrentActor)return false;

	float Distance = (GetActorLocation() - CurrentActor->GetActorLocation()).Size();

	if (Distance <600) 
		return true;
	
	
	if (Distance > 601)
		return false;

	return false;
}



void ARangeAttackBot::StartAttack()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(Timer)) return;
	auto BubbleController = Cast<ABubbleAIController>(GetController());
	if (!BubbleController)return ;

	AActor* CurrentActor = BubbleController->GetcurentActor();
	if (!CurrentActor)return ;

	if (!GetWorld())return;
	FTimerDelegate TimerDel;
	TimerDel.BindUFunction(this, FName("RangeAttack"), CurrentActor);
	GetWorld()->GetTimerManager().SetTimer(Timer, TimerDel, 0.8f, true);
	
}

void ARangeAttackBot::StopAttack()
{
	if (!GetWorld())return;
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	
}


void ARangeAttackBot::RangeAttack(AActor* Actor)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, GetActorLocation());
	FVector Location = GetActorLocation(); 
	FVector ForwardVector = GetActorForwardVector(); 
	FVector Offset = ForwardVector * 100.0f; 
	FVector SpawnLocation = Location + Offset;

	
	FVector Direction = (Actor->GetActorLocation() - SpawnLocation).GetSafeNormal();
	FRotator Rotation = Direction.Rotation();

	if (ProjectileClass) {

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, Rotation);

		if (Projectile) {
			FVector LaunchDirection = Rotation.Vector();
			Projectile->SetInitialVelocity(LaunchDirection);
		}

	}


}