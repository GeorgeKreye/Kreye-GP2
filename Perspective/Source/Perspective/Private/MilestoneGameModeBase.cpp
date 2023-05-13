// Fill out your copyright notice in the Description page of Project Settings.


#include "MilestoneGameModeBase.h"
#include "MilestoneGameStateBase.h"
#include "Perspective/Perspective.h"
#include "Player/MilestonePlayerState.h"
#include "Player/PlayerPawn.h"

// Constructor to set the game state
AMilestoneGameModeBase::AMilestoneGameModeBase()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	GameStateClass = AMilestoneGameStateBase::StaticClass();
	PlayerStateClass = AMilestonePlayerState::StaticClass();
	PlayerControllerClass = APlayerController::StaticClass();
}

void AMilestoneGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	LOG_G("Game started");
}

// End the game
void AMilestoneGameModeBase::EndGame()
{
	// TODO: Currently does nothing, should boot player to a game over screen
	LOG_G("Game ended");
}
