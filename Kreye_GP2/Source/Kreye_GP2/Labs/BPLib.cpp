// Fill out your copyright notice in the Description page of Project Settings.


#include "BPLib.h"

// MoveTowards definition
FVector UBPLib::MoveTowards(const FVector& StartPos, const FVector& EndPos, float MaxDistance)
{
	// Output variable
	FVector Output;
	
	// Determine difference between start position and end position
	const FVector VectorDifference = EndPos - StartPos;

	// Calculate maximum step in direction of end position
	FVector MaxStep = FVector(VectorDifference); // Clone difference vector
	MaxStep.Normalize(0.0001); // Normalize difference
	MaxStep *= MaxDistance; // Multiply normalized difference by maximum distance
	
	// Determine if distance between start and end is less than that of the maximum step that can be taken in that direction
	if (VectorDifference.Length() < MaxStep.Length())
	{
		// Store end position in output
		Output = FVector(EndPos);
	}
	else
	{
		// Calculate displacement from starting position of the size of the maximum step, and store in output
		Output = StartPos + MaxStep;
	}

	// Return
	return Output;
}
