// Fill out your copyright notice in the Description page of Project Settings.


#include "Milestone2AIPawn.h"
#include "Milestone2AIMovementComponent.h"
#include "VectorTypes.h"

// Sets default values
AMilestone2AIPawn::AMilestone2AIPawn() : CurrentWaypoint(0)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	// Create movement component
	MovementComponent = CreateDefaultSubobject<UMilestone2AIMovementComponent>(TEXT("Movement Component"));
	MovementComponent->ConfirmPawnOwner(this);
}

// Called when the game starts or when spawned
void AMilestone2AIPawn::BeginPlay()
{
	Super::BeginPlay();

	// Add current location to waypoints
	Waypoints.Add(GetActorLocation());
}

// Called every frame
void AMilestone2AIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMilestone2AIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Called to send input to movement component
void AMilestone2AIPawn::SendMovementInput(const FVector& Input) const
{
	MovementComponent->SetLastMovementInput(Input);
}

// Called to increment current waypoint pointer (looping if needed)
void AMilestone2AIPawn::IncrementCurrentWaypoint()
{
	// Increment
	CurrentWaypoint = (CurrentWaypoint + 1) % Waypoints.Num();
}

// Returns whether pawn is at current waypoint
bool AMilestone2AIPawn::AtCurrentWaypoint()
{
	return GetActorLocation().Equals(Waypoints[CurrentWaypoint]); 
}

// Returns whether movement vector can reach current waypoint
bool AMilestone2AIPawn::CanReachDestination(const FVector& MaxMovement)
{
	// Calculate distance to current waypoint
	const int Distance = (Waypoints[CurrentWaypoint] - GetActorLocation()).Length();
	
	// Return whether maximum movement can cover distance to current waypoint
	return MaxMovement.Length() > Distance;
}
