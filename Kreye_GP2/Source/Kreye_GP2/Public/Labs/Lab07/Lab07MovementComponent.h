// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Lab07MovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KREYE_GP2_API ULab07MovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULab07MovementComponent();

	// The maximum velocity of the object
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxVelocity;

	// The list of waypoints this object can travel to
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Movement)
	TArray<FVector> Waypoints;

	// The index of the waypoint currently being travelled to
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category = Movement)
	int CurrentWaypoint;

	// The owner of this component
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly)
	TObjectPtr<AActor> Owner;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Calculates the direction of movement towards the current waypoint this frame.
	 * @return A normalized@code FVector@endcode representing the direction of movement this frame.
	 */
	UFUNCTION(BlueprintPure, Category = Movement)
	FVector CalculateMovementDirection();

	/**
	 * @brief Checks whether the distance of the vector between the current position and the destination waypoint is
	 * less than the distance of the vector that determines the maximum movement this frame.
	 * @param Range The vector determining the range of movement for the current frame.
	 * @return @code true@endcode if the distance to the current waypoint is less than the maximum distance of movement
	 * this frame.
	 */
	UFUNCTION(BlueprintPure, Category = Movement)
	bool TargetInRange(const FVector& Range);
};
