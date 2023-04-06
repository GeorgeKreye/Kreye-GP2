// Fill out your copyright notice in the Description page of Project Settings.


#include "BounceSceneComponent.h"
#include "Kreye_GP2/Labs/BPLib.h"

// Sets default values for this component's properties
UBounceSceneComponent::UBounceSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Get owner
	Owner = GetOwner();
}


// Called when the game starts
void UBounceSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get initial position
	StartingPosition = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UBounceSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Get current position
	CurrentPosition = Owner->GetActorLocation();

	// Determine current target position
	FVector TargetPosition;
	if (IsReversed)
	{
		TargetPosition = StartingPosition;
	}
	else
	{
		TargetPosition = EndingPosition;
	}

	// Move towards target
	const FVector NewPosition = UBPLib::MoveTowards(CurrentPosition,TargetPosition,MaxSpeed);

	// Set actor location to new position
	Owner->SetActorLocation(NewPosition);

	// Check if new position is target
	if (NewPosition.Equals(TargetPosition,0.0001))
	{
		// Reverse direction of movement if at target
		IsReversed = !IsReversed;
	}
}

