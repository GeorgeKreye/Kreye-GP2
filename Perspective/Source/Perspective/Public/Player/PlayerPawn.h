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
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input);
	TSoftObjectPtr<class UInputMappingContext> PlayerInputMapping;

	UPROPERTY(EditAnywhere);
	float MaxMoveSpeed;

	virtual void Move(const struct FInputActionInstance& Instance);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector2d LastInput;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
