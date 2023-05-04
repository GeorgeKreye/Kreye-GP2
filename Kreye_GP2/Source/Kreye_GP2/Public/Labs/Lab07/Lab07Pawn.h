// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Lab07PawnMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Lab07Pawn.generated.h"

UCLASS()
class ALab07Pawn : public
APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALab07Pawn();

	// The mesh used by this pawn
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Mesh)
	TObjectPtr<UStaticMeshComponent> Mesh;

	// The camera used by this pawn
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = Camera)
	TObjectPtr<UCameraComponent> Camera;

	// The position of the pawn camera
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Camera)
	FVector CameraPosition;

	// The rotation of the pawn camera
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Camera)
	FRotator CameraRotation;

	// The input action used by the pawn for movement
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Input)
	TObjectPtr<UInputAction> MovementAction;
	
	// The input mapping context used by the pawn
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input)
	TSoftObjectPtr<UInputMappingContext> InputMap;
	
	// The movement component that is used to move the pawn
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Input)
	TObjectPtr<ULab07PawnMovementComponent> MovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief 
	 * @param Instance The movement input that has been received
	 */
	virtual void Move(const struct FInputActionInstance& Instance);
};
