// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WaypointSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KREYE_GP2_API UWaypointSceneComponent : public USceneComponent
{
	GENERATED_BODY()
	
	// Storage for waypoints
	UPROPERTY(EditAnywhere)
	TArray<FVector> Waypoints;
	
public:	
	// Sets default values for this component's properties
	UWaypointSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
