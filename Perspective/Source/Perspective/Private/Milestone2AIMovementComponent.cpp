// Fill out your copyright notice in the Description page of Project Settings.


#include "Milestone2AIMovementComponent.h"
#include "Milestone2AIPawn.h"

// Sets default values for this component's properties
UMilestone2AIMovementComponent::UMilestone2AIMovementComponent() : PawnOwner(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMilestone2AIMovementComponent::BeginPlay()
{
	// Call super
	Super::BeginPlay();

	// ...
}


// Called every frame
void UMilestone2AIMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	// Call super
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure it is possible to move this frame
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Calculate maximum movement this frame
	FVector MaxFrameMovement = LastMovementInput * DeltaTime * MaxVelocity;

	// Check if movement covers distance to destination
	FVector FrameMovement;
	if (Owner->CanReachDestination(MaxFrameMovement))
	{
		// Set frame movement to be distance to destination
		FrameMovement = Owner->Waypoints[Owner->CurrentWaypoint] - Owner->GetActorLocation();
	} else
	{
		// Set frame movement to maximum
		FrameMovement = MaxFrameMovement;
	}
	// Don't move if maximum movement is inconsequential
	if (!FrameMovement.IsNearlyZero())
	{
		// Perform movement
		FHitResult Hit;
		SafeMoveUpdatedComponent(FrameMovement, UpdatedComponent->GetComponentRotation(), true, Hit);

		// Attempt to slide if something was hit
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(FrameMovement, 1.f - Hit.Time, Hit.Normal, Hit);
		}

		// Reset last movement input
		LastMovementInput = FVector::ZeroVector;
	}
}

// Called to confirm owner is a pawn (should only be called by pawns for intended behavior)
void UMilestone2AIMovementComponent::ConfirmPawnOwner(TObjectPtr<AMilestone2AIPawn> Pawn)
{
	// Set PawnOwner to true
	PawnOwner = true;

	// Store pawn
	Owner = Pawn;
}

// Called to update the last received input
void UMilestone2AIMovementComponent::SetLastMovementInput(const FVector& Input)
{
	// Update last received input
	LastMovementInput = Input;
}
