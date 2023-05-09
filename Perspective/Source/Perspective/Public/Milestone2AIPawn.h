// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Milestone2AIMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Milestone2AIPawn.generated.h"

UCLASS()
class PERSPECTIVE_API AMilestone2AIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMilestone2AIPawn();

	/**
	 * @brief The mesh used by this pawn.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> Mesh;

	/**
	 * @brief The movement component used by this pawn.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<UMilestone2AIMovementComponent> MovementComponent;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Waypoints)
	TArray<FVector> Waypoints;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Waypoints)
	int CurrentWaypoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SendMovementInput(const FVector& Input) const;
	
	void IncrementCurrentWaypoint();

	/**
	 * @brief Checks whether this pawn has reached the current waypoint.
	 * @return @code true@endcode if the pawn is currently at the current waypoint.
	 */
	bool AtCurrentWaypoint();

	/**
	 * @brief Checks whether the maximum movement this frame can reach the current waypoint.
	 * @param MaxMovement The maximum movement this frame.
	 * @return @code true@endcode if maximum movement is enough to reach the current waypoint.
	 */
	bool CanReachDestination(const FVector& MaxMovement);
};
