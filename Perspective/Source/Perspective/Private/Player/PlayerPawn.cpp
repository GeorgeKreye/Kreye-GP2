// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Perspective/Perspective.h"
#include "EnhancedInputSubsystems.h"
#include "MilestoneGameModeBase.h"
#include "MilestoneGameStateBase.h"
#include "Camera/CameraComponent.h"
#include "Player/MilestonePlayerState.h"

// Sets default values
APlayerPawn::APlayerPawn() : CameraPosition(-300 * FMath::Cos(PI / 4), -300 * FMath::Sin(PI / 4), 300),
                             CameraRotation(-35.264, 45.0, 0), IsGrounded(false), FallOutZ(-5000)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);

	// Get input actions
	auto MovementAction = ConstructorHelpers::FObjectFinder<UInputAction>(
		TEXT("/Game/Inputs/PlayerMovementAction.PlayerMovementAction")); // Move
	if (MovementAction.Succeeded())
	{
		PlayerMovementAction = MovementAction.Object;
	}
	else
	{
		WARN("PlayerPawn: Could not find movement action");
	}
	auto JumpAction = ConstructorHelpers::FObjectFinder<UInputAction>(
		TEXT("/Game/Inputs/PlayerJumpAction.PlayerJumpAction")); // Jump
	if (JumpAction.Succeeded())
	{
		PlayerJumpAction = JumpAction.Object;
	}
	else
	{
		WARN("PlayerPawn: Could not find jump action");
	}
	auto Camera1 = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/Inputs/CameraChange/Camera1.Camera1"));
	// Change to Camera 1
	if (Camera1.Succeeded())
	{
		Camera1Action = Camera1.Object;
	}
	else
	{
		WARN("PlayerPawn: Could not find change to Camera 1 action");
	}
	auto Camera2 = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/Inputs/CameraChange/Camera2.Camera2"));
	// Change to Camera 2
	if (Camera2.Succeeded())
	{
		Camera2Action = Camera2.Object;
	}
	else
	{
		WARN("PlayerPawn: Could not find change to Camera 2 action");
	}
	auto Camera3 = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/Inputs/CameraChange/Camera3.Camera3"));
	// Change to Camera 3
	if (Camera3.Succeeded())
	{
		Camera3Action = Camera3.Object;
	}
	else
	{
		WARN("PlayerPawn: Could not find change to Camera 3 action");
	}
	auto Camera4 = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/Inputs/CameraChange/Camera4.Camera4"));
	// Change to Camera 4
	if (Camera4.Succeeded())
	{
		Camera4Action = Camera4.Object;
	}
	else
	{
		WARN("PlayerPawn: Could not find change to Camera 4 action");
	}

	// Get input mapping
	auto Input = ConstructorHelpers::FObjectFinder<UInputMappingContext>
		(TEXT("/Game/Inputs/PlayerInputMapping.PlayerInputMapping"));
	if (Input.Succeeded())
	{
		PlayerInputMapping = Input.Object;
	}
	else
	{
		WARN("PlayerPawn: Could not find input mapping");
	}

	// Create camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Edit camera transform
	Camera->SetRelativeLocation(CameraPosition);
	Camera->SetWorldRotation(CameraRotation);

	// Create movement component
	Movement = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Movement"));
	Movement->ConfirmPawnOwner();

	// Setup ground collision check
	OnActorHit.AddDynamic(this, &APlayerPawn::CheckForGround);
	
	// Tell mesh to check for collision
	StaticMesh->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	// Get game mode & state
	const TObjectPtr<UWorld> World = this->GetWorld();
	GameMode = World->GetAuthGameMode<AMilestoneGameModeBase>();
	if (GameMode != nullptr)
	{
		GameState = GameMode->GetGameState<AMilestoneGameStateBase>(); // TODO: Crash here
	}
	else
	{
		ERR("PlayerPawn: Incompatible gamemode detected, behavior is now unsupported");
	}

	// Get player state
	const TObjectPtr<APlayerController> SPlayerController = Cast<APlayerController>(GetController());
	if (SPlayerController != nullptr)
	{
		MPlayerState = SPlayerController->GetPlayerState<AMilestonePlayerState>();
	}
	else
	{
		ERR("PlayerPawn: Could not find a player controller");
	}

	// Assign and cast controller to a player controller
	if (const TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController()))
	{
		if (const TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(PlayerController->GetLocalPlayer()))
		{
			if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (!PlayerInputMapping.IsNull())
				{
					InputSystem->AddMappingContext(PlayerInputMapping.LoadSynchronous(), 0);
				}
				else
				{
					WARN("Mapping already exists!");
				}
			}
			else
			{
				WARN("Mapping failed at input system retrieval!");
			}
		}
		else
		{
			WARN("Mapping failed at local player retrieval!");
		}
	}
	else
	{
		WARN("Mapping failed at controller cast!");
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the camera should have its location changed
	UpdateCamera();

	// Check if player has fallen out of world
	CheckForFallOut();

	// Pass ground check
	Movement->SetGrounded(IsGrounded);

	// Reset ground check
	IsGrounded = false;
	
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	LOG("Getting enhanced input component");
	TObjectPtr<UEnhancedInputComponent> EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	LOG("Binding move actions");
	EIS->BindAction(PlayerMovementAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
	EIS->BindAction(PlayerJumpAction, ETriggerEvent::Triggered, this, &APlayerPawn::Jump);

	LOG("Binding camera actions");
	EIS->BindAction(Camera1Action, ETriggerEvent::Triggered, this, &APlayerPawn::ToCamera1);
	EIS->BindAction(Camera2Action, ETriggerEvent::Triggered, this, &APlayerPawn::ToCamera2);
	EIS->BindAction(Camera3Action, ETriggerEvent::Triggered, this, &APlayerPawn::ToCamera3);
	EIS->BindAction(Camera4Action, ETriggerEvent::Triggered, this, &APlayerPawn::ToCamera4);
}

// Send movement input when called
void APlayerPawn::Move(const struct FInputActionInstance& Instance)
{
	// Pass movement input to movement component
	Movement->SetLastMovementInput(Instance.GetValue().Get<FVector2d>());
}

// Send jump input when called
void APlayerPawn::Jump(const struct FInputActionInstance& Instance)
{
	// Pass jump input to movement component
	Movement->SetJump(Instance.GetValue().Get<bool>());
}

// Check for camera position/rotation changes
void APlayerPawn::UpdateCamera()
{
	// Get game state camera properties
	const int CurrentCamera = GameState->CurrentCamera;
	const FVector CameraPos = MPlayerState->GetCameraPosition(CurrentCamera);
	const FRotator CameraRot = MPlayerState->GetCameraRotation(CurrentCamera);

	// Update player camera if properties different from game state properties
	if (CameraPos != CameraPosition)
	{
		CameraPosition = CameraPos;
		LOG("Camera position updated");
	}
	if (CameraRot != CameraRotation)
	{
		CameraRotation = CameraRot;
		LOG("Camera rotation updated");
	}

	// Update camera component
	Camera->SetRelativeLocation(CameraPosition);
	Camera->SetWorldRotation(CameraRotation);
}

// Change to camera 1 on input
void APlayerPawn::ToCamera1(const struct FInputActionInstance& Instance)
{
	// Change to camera 1
	if (GameState->CurrentCamera != 0 && Instance.GetValue().Get<bool>())
	{
		GameState->ChangeCamera(0);
	}
}

// Change to camera 2 on input
void APlayerPawn::ToCamera2(const struct FInputActionInstance& Instance)
{
	// Change to camera 2
	if (GameState->CurrentCamera != 1 && Instance.GetValue().Get<bool>())
	{
		GameState->ChangeCamera(1);
	}
}

// Change to camera 3 on input
void APlayerPawn::ToCamera3(const struct FInputActionInstance& Instance)
{
	// Change to camera 3
	if (GameState->CurrentCamera != 2 && Instance.GetValue().Get<bool>())
	{
		GameState->ChangeCamera(2);
	}
}

// Change to camera 4 on input
void APlayerPawn::ToCamera4(const struct FInputActionInstance& Instance)
{
	// Change to camera 4
	if (GameState->CurrentCamera != 3 && Instance.GetValue().Get<bool>())
	{
		GameState->ChangeCamera(3);
	}
}

// Check for ground collision for resetting jump
void APlayerPawn::CheckForGround(AActor* Self, AActor* Other, FVector NormalImpulse, const FHitResult& Hit)
{
	const AActor* OtherActor = Hit.GetActor();
	if(OtherActor == nullptr)
	{
		WARN("PlayerPawn: Collision event fired despite other actor resolving to a null pointer");
		return;
	}
	
	// Make sure hit is valid
	if (Hit.IsValidBlockingHit())
	{
		// Check tag
		if (OtherActor->ActorHasTag(TEXT("Ground"))) // TODO: crashes here
		{
			// Make sure collision is in right direction
			FVector CollisionDirection = OtherActor->GetActorLocation() - Self->GetActorLocation();
			CollisionDirection.Normalize(0.001);
			if (CollisionDirection.Z < 0)
			{
				IsGrounded = true;
				LOG("Grounded check passed");
			}
		}
	}
}

// Check if player has fallen out of the world
void APlayerPawn::CheckForFallOut()
{
	// Check if player has fallen out of the world
	if (GetActorLocation().Z <= FallOutZ)
	{
		// Subtract life
		MPlayerState->RemoveLife();

		// Check for game over
		if (MPlayerState->Lives <= 0)
		{
			// Execute game over logic
			
			return;
		}
		
		// Reset position
		SetActorLocation(MPlayerState->StartPosition);
	}
}
