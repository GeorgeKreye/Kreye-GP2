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
	// Function for moving towards a target position
	UFUNCTION(BlueprintPure, Category = "Basic Movement")
	const FVector MoveTowards(const FVector& StartPos, const FVector& EndPos, float MaxDistance) const;
};
