// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "Lab9AIMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class KREYE_GP2_API ULab9AIMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	ULab9AIMovementComponent();

	/**
	 * @brief The speed at which the movement component will apply movement input
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Movement)
	float MovementVelocity;

	/**
	 * @brief Stores the provided input in the private@code LastMovementInput@endcode variable.
	 * @param Input The received input to store.
	 */
	UFUNCTION()
	void SetLastMovementInput(const FVector& Input);

private:
	/**
	 * @brief The last movement input received
	 */
	FVector LastMovementInput;
};
