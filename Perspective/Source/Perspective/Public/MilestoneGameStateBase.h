// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MilestoneGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PERSPECTIVE_API AMilestoneGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMilestoneGameStateBase();

	// The current camera; used to determine view as well as position of view-dependent objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	int CurrentCamera;
};
