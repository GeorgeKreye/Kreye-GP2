// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab07/Lab07PawnMovementComponent.h"

#include "Kreye_GP2/Kreye_GP2.h"

// Sets default values for this component's properties
ULab07PawnMovementComponent::ULab07PawnMovementComponent() : MaxVelocity(80.0),LastMovementInput(FVector2d::ZeroVector)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Wait for owner to confirm identity
	PawnOwner = false;
}


// Called when the game starts
void ULab07PawnMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULab07PawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure it is possible to perform movement
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Calculate movement this frame
	FVector FrameMovement = FVector(LastMovementInput.X,LastMovementInput.Y,0.0) * DeltaTime * MaxVelocity;

	// Don't move if maximum movement is inconsequential
	if (!FrameMovement.IsNearlyZero())
	{
		// Perform movement
		FHitResult Hit;
		SafeMoveUpdatedComponent(FrameMovement, UpdatedComponent->GetComponentRotation(), true, Hit);

		// Attempt slide if something was hit
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(FrameMovement, 1.f - Hit.Time, Hit.Normal, Hit);
		}

		// Reset last movement input
		LastMovementInput = FVector2d::ZeroVector;
	}
}

// Called to set last movement input
void ULab07PawnMovementComponent::SetLastMovementInput(const FVector2d& Input)
{
	// Copy over last input
	LastMovementInput = Input;
	LOG("Movement input recieved: (%d,%d)",LastMovementInput.X,LastMovementInput.Y);
}

// Confirms owner is a pawn
void ULab07PawnMovementComponent::ConfirmPawnOwner()
{
	PawnOwner = true;
}
