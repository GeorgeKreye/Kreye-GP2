// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Milestone2AIMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PERSPECTIVE_API UMilestone2AIMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMilestone2AIMovementComponent();

	/**
	 * @brief The maximum velocity this movement component can apply.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxVelocity;

	/**
	 * @brief The pawn that owns this movement component.
	 * Read-only as it should be set during construction via@code ConfirmPawnOwner()@endcode.
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Pawn)
	TObjectPtr<class AMilestone2AIPawn> Owner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief  Called by a pawn to confirm its identity and set itself as owner;
	 * should only be called by pawns for intended behavior.
	 * @param Pawn The AI Pawn calling the function
	 */
	void ConfirmPawnOwner(TObjectPtr<AMilestone2AIPawn> Pawn);

	/**
	 * @brief Called to set the last movement input, potentially triggering movement.
	 * @param Input The FVector representing the last input.
	 */
	void SetLastMovementInput(const FVector& Input);

private:
	/**
	 * @brief Whether this movement component is owned by a pawn (and therefore set up properly).
	 */
	bool PawnOwner;

	/**
	 * @brief The last input received for movement.
	 */
	FVector LastMovementInput;
};
