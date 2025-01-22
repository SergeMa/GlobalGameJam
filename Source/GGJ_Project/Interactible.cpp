// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactible.h"

// Add default functionality here for any IInteractible functions that are not pure virtual.

void IInteractible::Interact()
{
	if (GEngine) 
	{
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, FString::Printf(TEXT("Interacted with actor")));
	}
}