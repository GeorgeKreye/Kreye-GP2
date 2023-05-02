// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab07/Lab07MovementComponent.h"
#include "GameFramework/MovementComponent.h"

// Sets default values for this component's properties
ULab07MovementComponent::ULab07MovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Get owning actor
	Owner = GetOwner();
}


// Called when the game starts
void ULab07MovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// Add starting position to the end of the list of waypoints
	Waypoints.Add(Owner->GetActorLocation());
}


// Called every frame
void ULab07MovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure it is possible to perform movement
	if (!UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Calculate maximum movement this frame
	FVector MaxFrameMovement = CalculateMovementDirection() * DeltaTime * MaxVelocity;

	// Don't move if maximum movement is inconsequential
	if (!MaxFrameMovement.IsNearlyZero())
	{
		FVector FrameMovement;
		// Check if distance to current waypoint is less than maximum movement this frame
		if (TargetInRange(FrameMovement))
		{
			// Set movement this frame to be the distance to current waypoint
			FrameMovement = Waypoints[CurrentWaypoint] - Owner->GetActorLocation();
		}
		else
		{
			// Set movement this frame to maximum
			FrameMovement = MaxFrameMovement;
		}

		// Perform movement
		FHitResult Hit;
		SafeMoveUpdatedComponent(FrameMovement, UpdatedComponent->GetComponentRotation(), true, Hit);

		// Attempt slide if something was hit
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(FrameMovement, 1.f - Hit.Time, Hit.Normal, Hit);
		}

		// Check if at target
		if (Owner->GetActorLocation().Equals(Waypoints[CurrentWaypoint],0.001))
		{
			CurrentWaypoint = (CurrentWaypoint + 1) % Waypoints.Num();
		}
	}
	
}

// Calculates direction of movement
FVector ULab07MovementComponent::CalculateMovementDirection()
{
	// Get current location and destination
	const FVector Current = Owner->GetActorLocation();
	const FVector Destination = Waypoints[CurrentWaypoint];

	// Calculate distance vector between actor and destination
	FVector Direction = Destination - Current;

	// Normalize
	Direction.Normalize(0.001);

	// Return normalized vector
	return Direction;
}

// Checks whether target waypoint is within range of movement
bool ULab07MovementComponent::TargetInRange(const FVector& Range)
{
	// Get current location and destination
	const FVector Current = Owner->GetActorLocation();
	const FVector Destination = Waypoints[CurrentWaypoint];

	// Check and return if distance to destination is less than maximum movement distance this frame
	return (Destination - Current).Size() < Range.Size();
}
