// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "PlayerMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PERSPECTIVE_API UPlayerMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	UPlayerMovementComponent();

	/**
	 * @brief  Called by a pawn to confirm its identity;
	 * should only be called by pawns for intended behavior
	 */
	void ConfirmPawnOwner();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxVelocity;

	/**
	 * @brief Called to set the last movement input, potentially triggering movement.
	 * @param Input The FVector2d representing the last input.
	 */
	void SetLastMovementInput(const FVector2d& Input);

protected:
	virtual void BeginPlay() override;

private:
	// The last movement input received
	FVector2d LastMovementInput;

	// Whether this component is owned by a pawn (and therefore is set up correctly)
	bool PawnOwner;
};
