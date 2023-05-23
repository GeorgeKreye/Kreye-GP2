// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MilestoneGameStateBase.h"
#include "MilestonePlayerState.h"
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

	/**
	 * @brief The input action used for controlling the player's horizontal movement
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MovementInput)
	TObjectPtr<UInputAction> PlayerMovementAction;

	/**
	 * @brief The input action used for making the player jump
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MovementInput)
	TObjectPtr<UInputAction> PlayerJumpAction;

	/**
	 * @brief The input action used for changing to camera 1
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraInput)
	TObjectPtr<UInputAction> Camera1Action;

	/**
	 * @brief The input action used for changing to camera 2
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraInput)
	TObjectPtr<UInputAction> Camera2Action;

	/**
	 * @brief The input action used for changing to camera 3
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraInput)
	TObjectPtr<UInputAction> Camera3Action;

	/**
	 * @brief The input action used for changing to camera 4
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraInput)
	TObjectPtr<UInputAction> Camera4Action;

	/**
	 * @brief The game state
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Game)
	TObjectPtr<AMilestoneGameStateBase> GameState;

	/**
	 * @brief The player state
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Game)
	TObjectPtr<AMilestonePlayerState> MPlayerState;

	/**
	 * @brief The mesh used by the player character
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/**
	 * @brief The input map used by the player
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TSoftObjectPtr<class UInputMappingContext> PlayerInputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector CameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FRotator CameraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	TObjectPtr<UPlayerMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lives)
	int FallOutZ;

	/**
	 * @brief The game mode
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Game)
	TObjectPtr<AMilestoneGameModeBase> GameMode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief Called per frame to check where the camera should be.
	 */
	void UpdateCamera();

	/**
	 * @brief Receives movement input from the player
	 * @param Instance The movement input instance received
	 */
	virtual void Move(const struct FInputActionInstance& Instance);

	/**
	 * @brief Retrieves jump input from the player
	 * @param Instance The jump input instance received
	 */
	virtual void Jump(const struct FInputActionInstance& Instance);

	/**
	 * @brief Retrieves camera change input from the player; specifically handles camera 1
	 * @param Instance The camera change input received
	 */
	virtual void ToCamera1(const struct FInputActionInstance& Instance);

	/**
	 * @brief Retrieves camera change input from the player; specifically handles camera 2
	 * @param Instance The camera change input received
	 */
	virtual void ToCamera2(const struct FInputActionInstance& Instance);

	/**
	 * @brief Retrieves camera change input from the player; specifically handles camera 3
	 * @param Instance The camera change input received
	 */
	virtual void ToCamera3(const struct FInputActionInstance& Instance);

	/**
	 * @brief Retrieves camera change input from the player; specifically handles camera 4
	 * @param Instance The camera change input received
	 */
	virtual void ToCamera4(const struct FInputActionInstance& Instance);

	/**
	 * @brief Checks whether the pawn is touching the ground.
	 * @param Self This pawn
	 * @param Other The object being hit
	 * @param NormalImpulse Unused
	 * @param Hit The hit event
	 */
	UFUNCTION()
	void CheckForGround(AActor* Self, AActor* Other, FVector NormalImpulse, const FHitResult& Hit);

	/**
	 * @brief Checks whether the actor has fallen out of the world and removes a life if true.
	 */
	void CheckForFallOut();

	/**
	 * @brief Subtracts a life from the player, checking for a game over.
	 */
	UFUNCTION(BlueprintCallable,Category=Lives)
	void LoseLife();

private:
	/**
	 * @brief Checks whether the pawn is currently colliding with the ground.
	 */
	bool IsGrounded;
};
