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

	// The mesh used by this object
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StaticMesh)
	TObjectPtr<UStaticMeshComponent> Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
