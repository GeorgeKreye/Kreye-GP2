// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lab05RotationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KREYE_GP2_API ULab05RotationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULab05RotationComponent();
	
	/**
	 * @brief The maximum speed at which the actor can rotate
	 */
	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	/**
	 * @brief The vector used to determine the axis of rotation
	 */
	UPROPERTY(EditAnywhere)
	FVector RotationAxis;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
