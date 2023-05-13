// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerMovementComponent.h"
#include "Perspective/Perspective.h"

UPlayerMovementComponent::UPlayerMovementComponent() : MaxVelocity(250.0), PawnOwner(false), JumpVelocity(10.0)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check if it is possible to move
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Reset jump status if grounded
	if (IsGrounded && Jumping)
	{
		Jumping = false;
	}
	else if (!Jumping && IsGrounded && JumpThisFrame)
	{
		Jumping = true;
	}

	// Calculate movement this frame
	FVector FrameMovement = FVector(LastMovementInput, 0.0) * DeltaTime * MaxVelocity;
	if (Jumping)
	{
		FrameMovement.Z = JumpVelocity;
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

		// Reset input
		LastMovementInput = FVector2d::ZeroVector;
		JumpThisFrame = false;
	}
}

void UPlayerMovementComponent::ConfirmPawnOwner()
{
	PawnOwner = true;
}

// Sets last movement input when called
void UPlayerMovementComponent::SetLastMovementInput(const FVector2d& Input)
{
	LastMovementInput = Input;
}

// Sets whether to jump this frame when called
void UPlayerMovementComponent::SetJump(const bool& Jump)
{
	JumpThisFrame = Jump;
}

// Sets whether the player is grounded when called
void UPlayerMovementComponent::SetGrounded(const bool& Grounded)
{
	IsGrounded = Grounded;
}