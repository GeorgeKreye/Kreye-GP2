// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class PERSPECTIVE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	/**
	 * @brief The input action used for controlling the player's horizontal movement
	 */
	TObjectPtr<class UInputAction> PlayerMovementAction;

	UPROPERTY(EditAnywhere);
	/**
	 * @brief The mesh used by the player character
	 */
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	/**
	 * @brief The input map used by the player
	 */
	TSoftObjectPtr<class UInputMappingContext> PlayerInputMapping;

	UPROPERTY(EditAnywhere);
	/**
	 * @brief The maximum movement speed the player can horizontally move at
	 */
	float MaxMoveSpeed;

	/**
	 * @brief Receives movement input from the player
	 * @param Instance The movement input instance received
	 */
	virtual void Move(const struct FInputActionInstance& Instance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The last movement input made by the player
	FVector2d LastInput;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
