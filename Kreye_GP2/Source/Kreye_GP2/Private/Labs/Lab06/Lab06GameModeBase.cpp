// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab06/Lab06GameModeBase.h"
#include "Labs/Lab06/Lab06Pawn.h"
#include "Labs/Lab06/Lab06GameStateBase.h"

ALab06GameModeBase::ALab06GameModeBase()
{
	// Set default pawn class
	this->DefaultPawnClass = ALab06Pawn::StaticClass();

	// Set default game state
	this->GameStateClass = ALab06GameStateBase::StaticClass();
}
