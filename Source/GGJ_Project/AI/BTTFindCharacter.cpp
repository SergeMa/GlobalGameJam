// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_Project/AI/BTTFindCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GGJ_Project/PlayerPawn.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTFindCharacter::UBTTFindCharacter()
{
	NodeName = "FindCharacter";
}

EBTNodeResult::Type UBTTFindCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	if (!BlackBoard)return EBTNodeResult::Failed;

	FVector CharacterLocation;
	APlayerPawn* MyCharacter = Cast<APlayerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass()));
	if (MyCharacter)
	{
		CharacterLocation = MyCharacter->GetActorLocation();
	}

	BlackBoard->SetValueAsVector("Character", CharacterLocation);
	return EBTNodeResult::Succeeded;
	UE_LOG(LogTemp, Warning, TEXT("Actor Location: X=%f, Y=%f, Z=%f"), CharacterLocation.X, CharacterLocation.Y, CharacterLocation.Z);
}
