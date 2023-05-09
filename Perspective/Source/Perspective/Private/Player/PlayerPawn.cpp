// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Perspective/Perspective.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerPawn::APlayerPawn() : CameraPosition(-300 * FMath::Cos(PI / 4), -300 * FMath::Sin(PI / 4), 300),
                             CameraRotation(-35.264, 45.0, 0)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMesh);

	// Get input action
	auto Action = ConstructorHelpers::FObjectFinder<UInputAction>(
		TEXT("/Game/Inputs/PlayerMovementAction.PlayerMovementAction"));
	if (Action.Succeeded())
	{
		PlayerMovementAction = Action.Object;
	}
	else
	{
		WARN("PlayerPawn: Could not find movement action");
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
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

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
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	WARN("Getting enhanced input component");
	TObjectPtr<UEnhancedInputComponent> EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	WARN("Binding move actions");
	EIS->BindAction(PlayerMovementAction, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
}

void APlayerPawn::Move(const struct FInputActionInstance& Instance)
{
	// Pass movement input to movement component
	Movement->SetLastMovementInput(Instance.GetValue().Get<FVector2d>());
}
