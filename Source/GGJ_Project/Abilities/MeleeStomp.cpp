// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeStomp.h"

#include "NiagaraFunctionLibrary.h"
#include "Engine/DamageEvents.h"
#include "GGJ_Project/PlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"


UMeleeStomp::UMeleeStomp()
{
	PrimaryComponentTick.bCanEverTick = false;
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
}

void UMeleeStomp::BeginPlay()
{
	Super::BeginPlay();
	Audio->SetSound(SoundStomp);
	Audio->SetPaused(true);
}

void UMeleeStomp::UseAbility()
{
	Audio->Play(0);
	
	FVector Location = Player->GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	TArray<FHitResult> Hits;
	UKismetSystemLibrary::SphereTraceMultiForObjects(
		this,
		Location,
		Location,
		Range,
		ObjectTypes,
		false,
		{},
		EDrawDebugTrace::None,
		Hits,
		true);

	for(FHitResult Hit : Hits)
	{
		FDamageEvent DamageEvent;
		if (Hit.GetActor()) {
			Hit.GetActor()->TakeDamage(Damage, DamageEvent, GetWorld()->GetFirstPlayerController(), GetOwner());
		}
		UE_LOG(LogTemp, Display, TEXT("Actor was hit for %f damage!"), Damage);
	}
	SpawnSFX = UNiagaraFunctionLibrary::SpawnSystemAttached(Niagara, this, NAME_None, Player->GetActorLocation(), Player->GetActorRotation(), EAttachLocation::Type::KeepRelativeOffset, true);
	if(SpawnSFX)
	{
		SpawnSFX->SetVariableFloat(FName(TEXT("SFX_Range")), Range);
	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundStomp, Player->GetActorLocation());
}

void UMeleeStomp::UpgradeAbility()
{
	Super::UpgradeAbility();
	Range += RangeInc;
	Cooldown -= FMath::Clamp(CooldownInc, 1.f, 10.f);
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, this, &UAbility::UseAbility, Cooldown, true, false);

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Melee ability upgrade!"));
	}
}
