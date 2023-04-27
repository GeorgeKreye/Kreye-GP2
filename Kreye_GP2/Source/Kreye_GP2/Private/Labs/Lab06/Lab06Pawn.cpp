// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab06/Lab06Pawn.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Kreye_GP2/Kreye_GP2.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"

// Sets default values
ALab06Pawn::ALab06Pawn() : MaxMoveSpeed(10.0), CameraPosition(FVector(-200,0,BaseEyeHeight)), CameraRotation(FRotator(0,0,0)), LastInput(FVector2d::ZeroVector)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// Get default pawn mesh
	auto CapsuleMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	if (CapsuleMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CapsuleMesh.Object);
		Mesh->SetRelativeLocation(FVector(0.0,0.0,0.0));
	}
	else
	{
		WARN("Error: Could not find pawn mesh");
	}
	
	// Get default pawn material
	auto PawnMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor"));
	if(PawnMaterial.Succeeded())
	{
		Mesh->SetMaterial(0,PawnMaterial.Object);
	}
	else
	{
		WARN("Error: Could not find pawn material");
	}
	
	// Get pawn movement action
	auto InputAction = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/Labs/Lab06/Input/Lab06MovementAction.Lab06MovementAction"));
	if (InputAction.Succeeded())
	{
		MovementAction = InputAction.Object;
	}
	else
	{
		WARN("Error: Could not find pawn movement action");
	}

	// Get pawn input mapping
	auto InputMapping = ConstructorHelpers::FObjectFinder<UInputMappingContext>(TEXT("/Game/Labs/Lab06/Input/Lab06MappingContext.Lab06MappingContext"));
	if (InputMapping.Succeeded())
	{
		InputMap = InputMapping.Object;
	}
	else
	{
		WARN("Error: Could not find pawn input map");
	}

	// Create camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);

	// Edit camera transform
	Camera->SetRelativeLocation(CameraPosition);
	LOG("Relative camera position: (%d,%d,%d)",CameraPosition.X,CameraPosition.Y,CameraPosition.Z);
	Camera->SetRelativeRotation(CameraRotation);
	LOG("Relative camera rotation: (%d,%d,%d)",CameraRotation.Pitch,CameraRotation.Yaw,CameraRotation.Roll);
}

// Called when the game starts or when spawned
void ALab06Pawn::BeginPlay()
{
	Super::BeginPlay();

	// Assign and cast controller to a player controller
	LOG("Attempting to set up input mapping to controller");
	if (const TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController()))
	{
		if (const TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(PlayerController->GetLocalPlayer()))
		{
			if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (!InputMap.IsNull())
				{
					InputSystem->AddMappingContext(InputMap.LoadSynchronous(),0);
				}
				else
				{
					WARN("ERROR: No mapping context to use! (InputMap is null)");
				}
			}
			else
			{
				WARN("ERROR: Mapping failed at input system retrieval!");
			}
		}
		else
		{
			WARN("ERROR: Mapping failed at local player retrieval!");
		}
	}
	else
	{
		WARN("ERROR: Mapping failed at controller cast!");
	}
}

// Called every frame
void ALab06Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move pawn if movement has been received
	const FVector Movement = FVector(LastInput.X * MaxMoveSpeed,LastInput.Y * MaxMoveSpeed,0);
	const FVector UpdatedLocation = GetActorLocation() + Movement;
	SetActorLocation(UpdatedLocation);

	// Reset input
	LastInput = FVector2d::ZeroVector;
}

// Called to bind functionality to input
void ALab06Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get enhanced input component
	LOG("Getting enhanced input component");
	TObjectPtr<UEnhancedInputComponent> EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind movement action to enhanced input component
	LOG("Binding move actions");
	EIS->BindAction(MovementAction,ETriggerEvent::Triggered,this,&ALab06Pawn::Move);
}

// Called when movement is inputted
void ALab06Pawn::Move(const FInputActionInstance& Instance)
{
	// Pass received movement input vector to LastInput
	LastInput = Instance.GetValue().Get<FVector2d>();
	LOG("Move input: (%f, %f)",LastInput.X,LastInput.Y);
}


