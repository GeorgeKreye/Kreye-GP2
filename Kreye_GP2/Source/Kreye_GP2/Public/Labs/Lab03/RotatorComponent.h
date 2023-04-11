// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RotatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KREYE_GP2_API URotatorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotatorComponent();

	// Field for speed of rotation
	UPROPERTY(EditAnywhere);
	/**
	 * The speed of rotation of this object
	 */
	float RotationSpeed;

	// Owner property
	UPROPERTY(VisibleInstanceOnly);
	/**
	 * The Actor that is the parent of this SceneComponent
	 */
	AActor* Owner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
