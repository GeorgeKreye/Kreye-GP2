// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WaypointSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KREYE_GP2_API UWaypointSceneComponent : public USceneComponent
{
	GENERATED_BODY()
	
	
public:
	// Holds the array of waypoints that can be moved to
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FVector> Waypoints;

	// The maximum speed (delta distance) that can be traveled in a single tick
	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	// The Actor that owns this instance
	UPROPERTY(VisibleInstanceOnly)
	AActor* Owner;

	// The array index of the current target waypoint
	UPROPERTY(VisibleAnywhere)
	int CurrentTarget;
	
	// Sets default values for this component's properties
	UWaypointSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
