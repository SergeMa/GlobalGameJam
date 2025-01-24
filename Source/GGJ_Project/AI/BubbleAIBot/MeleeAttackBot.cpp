// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_Project/AI/BubbleAIBot/MeleeAttackBot.h"
#include "Components\CapsuleComponent.h"
#include "GGJ_Project/PlayerPawn.h"
#include "Engine/DamageEvents.h"
#include "Animation/AnimMontage.h"

AMeleeAttackBot::AMeleeAttackBot()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMeleeAttackBot::OnCollisionOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMeleeAttackBot::OnCollisionEndOverlap);

}


void AMeleeAttackBot::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetWorld())return;
	if (OtherActor->IsA<APlayerPawn>()) {
		
		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("MeeleAttack"), OtherActor);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 0.9, true);

	}
}

void AMeleeAttackBot::OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!GetWorld())return;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
void AMeleeAttackBot::MeeleAttack(AActor* Actor)
{
	GetActorLocation()=  GetActorForwardVector() * 1000;
	PlayAnimMontage(AnimMontage);
	FDamageEvent DEvent;
	Actor->TakeDamage(10, DEvent, Controller, this);

}