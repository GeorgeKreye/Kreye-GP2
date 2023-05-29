// Fill out your copyright notice in the Description page of Project Settings.


#include "PerspectiveV2/Public/Player/PerspectivePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APerspectivePlayerCharacter::APerspectivePlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Make sure player character is not affected by controller
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Get player character movement component
	const TObjectPtr<UCharacterMovementComponent> PlayerMovement = GetCharacterMovement();

	// Setup player character movement orientation
	PlayerMovement->bOrientRotationToMovement = true; // Orient player character to the direction of movement
	PlayerMovement->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // Sets rotation rate for movement orientation

	// Setup player character movement params w/ default values
	PlayerMovement->JumpZVelocity = 700.0f;
	PlayerMovement->AirControl = 0.35f;
	PlayerMovement->MaxWalkSpeed = 500.0f;
	PlayerMovement->MinAnalogWalkSpeed = 20.0f;
	PlayerMovement->BrakingDecelerationWalking = 2000.0f;

	// Create camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = false;
	// Don't rotate based on controller since fixed camera angles are being used
}

// Called when the game starts or when spawned
void APerspectivePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMap, 0);
		}
	}
}

// Called every frame
void APerspectivePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APerspectivePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind input mappings
	if (UEnhancedInputComponent* EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jump action
		EIS->BindAction(JumpAction,ETriggerEvent::Triggered,this, &ACharacter::Jump);
		EIS->BindAction(JumpAction,ETriggerEvent::Completed,this, &ACharacter::StopJumping);

		// Movement action
		EIS->BindAction(MoveAction,ETriggerEvent::Triggered,this, &APerspectivePlayerCharacter::Move);

		// Camera change actions
		EIS->BindAction(Camera1Action,ETriggerEvent::Triggered,this,&APerspectivePlayerCharacter::Camera1Change);
		EIS->BindAction(Camera2Action,ETriggerEvent::Triggered,this,&APerspectivePlayerCharacter::Camera2Change);
		EIS->BindAction(Camera3Action,ETriggerEvent::Triggered,this,&APerspectivePlayerCharacter::Camera3Change);
		EIS->BindAction(Camera4Action,ETriggerEvent::Triggered,this,&APerspectivePlayerCharacter::Camera4Change);
	}
}

// Movement input
void APerspectivePlayerCharacter::Move(const FInputActionValue& Value)
{
	// Get movement vector
	const FVector2d MovementVector = Value.Get<FVector2d>();

	// Don't do anything if there is no controller to use to apply movement
	if (Controller != nullptr)
	{
		// Find forward rotation
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator ForwardRotation(0, Rotation.Yaw, 0);

		// Get forward vector and right vector
		const FRotationMatrix RotationMatrix = FRotationMatrix(ForwardRotation);
		const FVector ForwardVector = RotationMatrix.GetUnitAxis(EAxis::X);
		const FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);

		// Apply movement
		AddMovementInput(ForwardVector,MovementVector.Y);
		AddMovementInput(RightVector,MovementVector.X);
	}
}

// Camera change to camera 1
void APerspectivePlayerCharacter::Camera1Change(const FInputActionValue& Value)
{
	// Make sure boolean is true
	if (Value.Get<bool>())
	{
		CurrentCamera = 0;
	}
}

// Camera change to camera 2
void APerspectivePlayerCharacter::Camera2Change(const FInputActionValue& Value)
{
	// Make sure boolean is true
	if (Value.Get<bool>())
	{
		CurrentCamera = 1;
	}
}

// Camera change to camera 3
void APerspectivePlayerCharacter::Camera3Change(const FInputActionValue& Value)
{
	// Make sure boolean is true
	if (Value.Get<bool>())
	{
		CurrentCamera = 2;
	}
}

// Camera change to camera 4
void APerspectivePlayerCharacter::Camera4Change(const FInputActionValue& Value)
{
	// Make sure boolean is true
	if (Value.Get<bool>())
	{
		CurrentCamera = 3;
	}
}
