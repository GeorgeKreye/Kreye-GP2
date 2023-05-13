// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Milestone2AIPawn.h"
#include "Milestone2AIController.generated.h"

/**
 * 
 */
UCLASS()
class PERSPECTIVE_API AMilestone2AIController : public AAIController
{
	GENERATED_BODY()

public:
	AMilestone2AIController();

	virtual void Tick(float DeltaSeconds) override;

	/**
	 * @brief The pawn controlled by the AI.
	 * Cannot be set manually, as it will be set on game start based on setup in the editor.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Pawn)
	TObjectPtr<AMilestone2AIPawn> AIPawn;

	
	/**
	 * @brief Has the AI-controlled pawn move towards the current waypoint.
	 * @param AIPawn The pawn controlled by the AI.
	 */
	UFUNCTION()
	void GoToWaypoint();

protected:
	virtual void BeginPlay() override;
};
