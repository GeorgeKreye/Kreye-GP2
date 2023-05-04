// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Lab07PawnMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KREYE_GP2_API ULab07PawnMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULab07PawnMovementComponent();

	// The maximum velocity that the movement component can move at
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Movement)
	float MaxVelocity;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called to set last movement input
	void SetLastMovementInput(const FVector2d& Input);

	/**
	 * @brief  Called by a pawn to confirm its identity; should only be called by pawns for intended behavior
	 */
	void ConfirmPawnOwner();

private:
	// Whether the component is confirmed to be attached to a pawn
	bool PawnOwner;
	
	// The last movement input received
	FVector2D LastMovementInput;
};
