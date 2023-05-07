// Fill out your copyright notice in the Description page of Project Settings.


#include "MilestoneGameModeBase.h"
#include "MilestoneGameStateBase.h"
#include "Perspective/Perspective.h"
#include "Player/PlayerPawn.h"

// Constructor to set the game state
AMilestoneGameModeBase::AMilestoneGameModeBase()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	GameStateClass = AMilestoneGameStateBase::StaticClass();
}

void AMilestoneGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	LOG_G("Game started");
}

void AMilestoneGameModeBase::EndGame()
{
	LOG_G("Game ended");
}
