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
	
	void SetAudioComponent(TObjectPtr<UAudioComponent> Component);
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly)
	TObjectPtr<UAudioComponent> AudioComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float JumpVelocity;

	

	/**
	 * @brief Called to set the last movement input, potentially triggering movement.
	 * @param Input The FVector2d representing the last input.
	 */
	void SetLastMovementInput(const FVector2d& Input);

	/**
	 * @brief Tells the movement component to jump this frame if the passed in value is @code true@endcode.
	 * @param Jump Whether to jump this frame
	 */
	void SetJump(const bool& Jump);

	/**
	 * @brief Tells the movement component whether the player is currently grounded.
	 * @param Grounded Whether the player is grounded
	 */
	void SetGrounded(const bool& Grounded);

protected:
	// Called before first frame
	virtual void BeginPlay() override;

private:
	// The last movement input received
	FVector2d LastMovementInput;

	// Whether this component is owned by a pawn (and therefore is set up correctly)
	bool PawnOwner;

	// Whether to perform a jump this frame
	bool JumpThisFrame;

	// Whether the player is currently grounded
	bool IsGrounded;

	// Whether the player is in the middle of a jump
	bool Jumping;
};
