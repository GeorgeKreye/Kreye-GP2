// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MilestonePlayerState.h"

AMilestonePlayerState::AMilestonePlayerState()
{
	// Construct list of camera positions
	CameraPositions.Add(FVector(-300 * FMath::Cos(PI / 4), -300 * FMath::Sin(PI / 4), 300));
	CameraPositions.Add(FVector(300 * FMath::Cos(PI / 4), -300 * FMath::Sin(PI / 4), 300));
	CameraPositions.Add(FVector(300 * FMath::Cos(PI / 4), 300 * FMath::Sin(PI / 4), 300));
	CameraPositions.Add(FVector(-300 * FMath::Cos(PI / 4), 300 * FMath::Sin(PI / 4), 300));

	// Construct list of camera rotations
	CameraRotations.Add(FRotator(-35.264, 45.0, 0));
	CameraRotations.Add(FRotator(-35.264, 135.0, 0));
	CameraRotations.Add(FRotator(-35.264, 225.0, 0));
	CameraRotations.Add(FRotator(-35.264, 315.0, 0));
}

// Called every frame
void AMilestonePlayerState::Tick(float DeltaSeconds)
{
	
}

// Adds one or more lives
void AMilestonePlayerState::AddLife(const int Amount)
{
	// Add amount to determine new lives count
	Lives += Amount;
}

// Removes one or more lives; player pawn should check for game over
void AMilestonePlayerState::RemoveLife(const int Amount)
{
	// Subtract amount of lives to remove
	Lives -= Amount;
}

FVector AMilestonePlayerState::GetCameraPosition(const int& Camera) const
{
	return CameraPositions[Camera];
}

FRotator AMilestonePlayerState::GetCameraRotation(const int& Camera) const
{
	return CameraRotations[Camera];
}
