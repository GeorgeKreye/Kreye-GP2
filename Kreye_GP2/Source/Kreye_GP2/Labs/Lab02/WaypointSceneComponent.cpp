// Fill out your copyright notice in the Description page of Project Settings.


#include "WaypointSceneComponent.h"
#include "Kreye_GP2/Labs/BPLib.h"

// Sets default values for this component's properties
UWaypointSceneComponent::UWaypointSceneComponent() : CurrentTarget(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Get owner
	Owner = GetOwner();
}


// Called when the game starts
void UWaypointSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// Add starting position to list of waypoints
	Waypoints.Add(Owner->GetActorLocation());
}


// Called every frame
void UWaypointSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get current position
	const FVector CurrentPosition = Owner->GetActorLocation();

	// Get current target position from waypoints
	const FVector TargetPosition = Waypoints[CurrentTarget];

	// Get new position to move to
	const FVector NewPosition = UBPLib::MoveTowards(CurrentPosition,TargetPosition,MaxSpeed);

	// Move to new position
	Owner->SetActorLocation(NewPosition);

	// Check if actor is now at target position
	if (NewPosition.Equals(TargetPosition,0.0001))
	{
		// Increment down waypoint array, looping back if the end is reached
		CurrentTarget = (CurrentTarget + 1) % Waypoints.Num();
	}
}

