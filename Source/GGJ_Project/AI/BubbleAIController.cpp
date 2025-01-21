// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_Project/AI/BubbleAIController.h"
#include "BehaviorTree/BehaviorTree.h"

void ABubbleAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BT);
}
