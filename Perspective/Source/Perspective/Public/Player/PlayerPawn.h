// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMovementComponent.h"
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

	/**
	 * @brief Receives movement input from the player
	 * @param Instance The movement input instance received
	 */
	virtual void Move(const struct FInputActionInstance& Instance);
	
	virtual void Jump(const struct FInputActionInstance& Instance);

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Camera);
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera);
	FVector CameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera);
	FRotator CameraRotation;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Movement)
	TObjectPtr<UPlayerMovementComponent> Movement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
