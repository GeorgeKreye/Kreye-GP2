// Fill out your copyright notice in the Description page of Project Settings.


#include "BPLib.h"

/**
 * Calculates a movement step from a starting position to an ending position with a maximum distance
 * @param StartPos A@code FVector@endcode that determines the starting position of movement
 * @param EndPos A@code FVector@endcode that determines the ending/target position of movement
 * @param MaxDistance A@code float@endcode that determines the maximum movement step
 * @returns A@code FVector@endcode that is between the starting position and end position that is at most@code maxDistance@endcode code away
 */
const FVector UBPLib::MoveTowards(const FVector& StartPos, const FVector& EndPos, float MaxDistance) const
{
	// Output variable
	FVector output;
	
	// Determine difference between start position and end position
	const FVector VectorDifference = EndPos - StartPos;

	// Calculate maximum step in direction of end position
	FVector MaxStep = FVector(VectorDifference); // Clone difference vector
	MaxStep.Normalize(0.0001); // Normalize difference
	MaxStep *= MaxDistance; // Multiply normalized difference by maximum distance
	
	// // Normalize difference
	// FVector NormalizedDifference = FVector(VectorDifference);
	// NormalizedDifference.Normalize(0.0001);
	//
	// // Multiply normalized difference by maximum distance 
	// const FVector MaxStep = NormalizedDifference * MaxDistance;
	
	// Determine if distance between start and end is less than that of the maximum step that can be taken in that direction
	if (VectorDifference.Length() < MaxStep.Length())
	{
		// Store end position in output
		output = FVector(EndPos);
	}
	else
	{
		// Calculate displacement from starting position of the size of the maximum step, and store in output
		output = StartPos + MaxStep;
	}

	// Return
	return output;
}
