// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BounceSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KREYE_GP2_API UBounceSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBounceSceneComponent();

	// The maximum traversal speed for movement
	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	// Stores the initial position
	UPROPERTY(VisibleAnywhere)
	FVector StartingPosition;

	// Stores the current position
	UPROPERTY(VisibleAnywhere)
	FVector CurrentPosition;
	
	// Determines the ending position
	UPROPERTY(EditAnywhere)
	FVector EndingPosition;

	// Determines whether the current direction of movement is reversed
	UPROPERTY(VisibleAnywhere)
	bool IsReversed;

	// The actor that owns this BounceSceneComponent
	UPROPERTY(VisibleInstanceOnly);
	AActor* Owner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
