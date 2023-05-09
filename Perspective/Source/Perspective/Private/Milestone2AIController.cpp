// Fill out your copyright notice in the Description page of Project Settings.


#include "Milestone2AIController.h"
#include "Milestone2AIPawn.h"
#include "Perspective/Perspective.h"

class AMilestone2AIPawn;

AMilestone2AIController::AMilestone2AIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMilestone2AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (AIPawn != nullptr)
	{
		GoToWaypoint();
		
	}
}

void AMilestone2AIController::BeginPlay()
{
	Super::BeginPlay();

	// Make sure AI is controlling something it can control
	AIPawn = GetPawn<AMilestone2AIPawn>();
	if (AIPawn == nullptr)
	{
		WARN("Milestone2A1Conttroller - Could not find an AI pawn to control");
	}
}

// 
void AMilestone2AIController::GoToWaypoint()
{
	// Get current location and destination
	const FVector Current = AIPawn->GetActorLocation();
	const FVector Destination = AIPawn->Waypoints[AIPawn->CurrentWaypoint];

	// Get movement direction
	FVector DistanceVector = Destination - Current;
	FVector TravelVector = FVector(DistanceVector);
	TravelVector.Normalize(0.001);

	// Send movement input
	AIPawn->SendMovementInput(TravelVector);

	// Check if the pawn is now at the current waypoint
	if (AIPawn->AtCurrentWaypoint())
	{
		// Go to next waypoint, looping back if the end of the waypoint list is reached
		AIPawn->IncrementCurrentWaypoint();
	}
}
