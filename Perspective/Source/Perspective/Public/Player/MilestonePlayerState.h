// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MilestoneGameModeBase.h"
#include "MilestoneGameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "MilestonePlayerState.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PERSPECTIVE_API AMilestonePlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AMilestonePlayerState();

	virtual void Tick(float DeltaSeconds) override;

	// The location where the player spawns on death
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Spawning)
	FVector StartPosition;

	// The number of lives the player has left
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Lives)
	int Lives;

	// The game mode of the game
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly, Category = Game)
	TObjectPtr<AMilestoneGameModeBase> GameMode;

	// The game state of the game
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly, Category= Game)
	TObjectPtr<AMilestoneGameStateBase> GameState;
	
	/**
	 * @brief Adds a life to the player
	 * @param Amount The amount of lives to add; defaults to 1
	 */
	UFUNCTION(BlueprintCallable, Category=Lives)
	void AddLife(const int Amount = 1);

	/**
	 * @brief Removes one or more lives from the player.
	 * @param Amount The amount of lives to remove; defaults to 1.
	 */
	UFUNCTION(BlueprintCallable, Category=Lives)
	void RemoveLife(const int Amount = 1);

	/**
	 * @brief Gets the position of a given camera
	 * @param Camera The camera #
	 * @return A FVector representing the camera's position
	 */
	UFUNCTION(Category=Camera)
	FVector GetCameraPosition(const int& Camera) const;

	/**
	 * @brief Gets the rotation of a given camera
	 * @param Camera The camera #
	 * @return A FRotator representing the camera's position
	 */
	UFUNCTION(Category=Camera)
	FRotator GetCameraRotation(const int& Camera) const;

private:
	// List of camera positions
	TArray<FVector> CameraPositions;
	
	// List of camera rotations
	TArray<FRotator> CameraRotations;

	// Current position of the camera
	FVector CurrentCameraPosition;

	// Current rotation of the camera
	FRotator CurrentCameraRotation;
};
