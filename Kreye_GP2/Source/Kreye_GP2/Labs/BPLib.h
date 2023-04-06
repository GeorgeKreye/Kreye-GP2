// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPLib.generated.h"

/**
 * 
 */
UCLASS()
class KREYE_GP2_API UBPLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Calculates a movement step from a starting position to an ending position with a maximum distance.
	* @param StartPos A@code FVector@endcode that determines the starting position of movement
	* @param EndPos A@code FVector@endcode that determines the ending/target position of movement
	* @param MaxDistance A@code float@endcode that determines the maximum delta distance that can be moved in one step
	* @returns A@code FVector@endcode that is between the starting position and end position that is at most@code maxDistance@endcode away
	*/
	UFUNCTION(BlueprintPure, Category = "Basic Movement")
	static FVector MoveTowards(
		UPARAM(DisplayName="Start Position") const FVector& StartPos,
		UPARAM(DisplayName="End Position") const FVector& EndPos,
		UPARAM(DisplayName="Maximum Distance (Delta)") float MaxDistance);
};
