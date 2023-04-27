// Fill out your copyright notice in the Description page of Project Settings.


#include "MilestoneGameModeBase.h"
#include "MilestoneGameStateBase.h"
#include "Player/PlayerPawn.h"

// Constructor to set the game state
AMilestoneGameModeBase::AMilestoneGameModeBase()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	GameStateClass = AMilestoneGameStateBase::StaticClass();
}
