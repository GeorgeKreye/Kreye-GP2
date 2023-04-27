// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Lab06Pawn.generated.h"

UCLASS()
class KREYE_GP2_API ALab06Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALab06Pawn();

	/**
	 * @brief The mesh used by this pawn
	 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;

	/**
	 * @brief The maximum movement speed that this pawn can move horizontally
	 */
	UPROPERTY(EditAnywhere)
	float MaxMoveSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief Recieves movement input from the controller
	 * @param Instance The movement input instance recieved
	 */
	virtual void Move(const struct FInputActionInstance& Instance);
};
