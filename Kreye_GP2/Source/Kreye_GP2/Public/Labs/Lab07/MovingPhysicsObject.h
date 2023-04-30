// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPhysicsObject.generated.h"

UCLASS()
class KREYE_GP2_API AMovingPhysicsObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPhysicsObject();

	// The speed that the object can move at
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MoveSpeed;

	// The waypoints used for movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	TArray<FVector> Waypoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
