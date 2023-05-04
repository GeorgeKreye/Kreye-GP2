// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lab07Trigger.generated.h"

UCLASS()
class KREYE_GP2_API ALab07Trigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALab07Trigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TObjectPtr<UStaticMeshComponent> Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when trigger has been hit
	UFUNCTION()
	void OnTriggerHit(AActor* Self, AActor* Other, FVector NormalImpulse, const FHitResult& Hit);
};
