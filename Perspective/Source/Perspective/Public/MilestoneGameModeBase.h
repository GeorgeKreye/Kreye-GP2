// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MilestoneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PERSPECTIVE_API AMilestoneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMilestoneGameModeBase();

	/**
	 * @brief Used to tell the game to end
	 */
	UFUNCTION()
	void EndGame();

protected:
	virtual void BeginPlay() override;
};
