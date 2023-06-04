// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PerspectivePlayerCharacter.generated.h"


class UInputAction;
class UInputMappingContext;
class UCameraComponent;

UCLASS(Blueprintable, Config=Game)
class PERSPECTIVEV2_API APerspectivePlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	/////////////////////////////////////////////////////////////////
	/// Functions
public:
	// Sets default values for this character's properties
	APerspectivePlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** @brief Function called when movement input is received */
	void Move(const FInputActionValue& Value);

	/** @brief Function called when camera change input is received; specifically handles camera 1*/
	void Camera1Change(const FInputActionValue& Value);

	/** @brief Function called when camera change input is received; specifically handles camera 2*/
	void Camera2Change(const FInputActionValue& Value);

	/** @brief Function called when camera change input is received; specifically handles camera 3*/
	void Camera3Change(const FInputActionValue& Value);

	/** @brief Function called when camera change input is received; specifically handles camera 4*/
	void Camera4Change(const FInputActionValue& Value);

	/////////////////////////////////////////////////////////////////
	/// Variables
public:
	/** @brief The camera used by the player */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	/** @brief The input mapping context used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMap;

	/** @brief The input action used for registering a jump */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** @brief The input action used for movement */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** @brief The input action used to change the camera to position 1 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Camera1Action;

	/** @brief The input action used to change the camera to position 2 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Camera2Action;

	/** @brief The input action used to change the camera to position 3 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Camera3Action;

	/** @brief The input action used to change the camera to position 4 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Camera4Action;

	/** @brief The current camera; should be passed to the game state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	int CurrentCamera;
};
