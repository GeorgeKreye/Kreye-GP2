// Fill out your copyright notice in the Description page of Project Settings.


#include "BPLib.h"


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
