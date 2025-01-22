// Fill out your copyright notice in the Description page of Project Settings.


#include "BubblesGameMode.h"

ABubblesGameMode::ABubblesGameMode() : DifficultyLevel(0) {}

int ABubblesGameMode::GetDifficultyLevel() const { return DifficultyLevel; }

void ABubblesGameMode::IncrementDifficultyLevel() { DifficultyLevel++; }