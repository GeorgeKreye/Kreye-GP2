// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MilestonePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PERSPECTIVE_API AMilestonePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMilestonePlayerState();

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Spawning)
	FVector StartPosition;
};
