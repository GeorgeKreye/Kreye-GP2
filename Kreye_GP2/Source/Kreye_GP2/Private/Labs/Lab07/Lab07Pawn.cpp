// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab07/Lab07Pawn.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kreye_GP2/Kreye_GP2.h"
#include "Labs/Lab07/Lab07PawnMovementComponent.h"

// Sets default values
ALab07Pawn::ALab07Pawn() : CameraPosition(-300,0,300), CameraRotation(-45,0,0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	// // Get capsule mesh
	// auto CapsuleMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	// if (CapsuleMesh.Succeeded())
	// {
	// 	Mesh->SetStaticMesh(CapsuleMesh.Object);
	// 	Mesh->SetRelativeLocation(FVector(0.0,0.0,0.0));
	// }
	//
	// // Get material
	// auto MeshMaterial = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("/Game/StarterContent/Materials/M_AssetPlatform.M_AssetPlatform"));
	// if (MeshMaterial.Succeeded())
	// {
	// 	Mesh->SetMaterial(0,MeshMaterial.Object);
	// }

	// Create camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);

	// Set camera transform
	Camera->SetRelativeLocation(CameraPosition);
	Camera->SetRelativeRotation(FQuat::MakeFromRotator(CameraRotation));

	// Create movement component
	MovementComponent = CreateDefaultSubobject<ULab07PawnMovementComponent>(TEXT("Movement Component"));
	MovementComponent->ConfirmPawnOwner();

	// Get input mapping
	auto InputContext = ConstructorHelpers::FObjectFinder<UInputMappingContext>(TEXT("/Game/Labs/Lab07/Input/Lab07Mapping.Lab07Mapping"));
	if (InputContext.Succeeded())
	{
		InputMap = InputContext.Object;
	}

	// Get movement action
	auto MovementInputAction = ConstructorHelpers::FObjectFinder<UInputAction>(TEXT("/Game/Labs/Lab07/Input/Lab07MovementAction.Lab07MovementAction"));
	if (MovementInputAction.Succeeded())
	{
		MovementAction = MovementInputAction.Object;
	}
}

// Called when the game starts or when spawned
void ALab07Pawn::BeginPlay()
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
					InputSystem->AddMappingContext(InputMap.LoadSynchronous(), 0);
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
void ALab07Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALab07Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get enhanced input component
	LOG("Getting enhanced input component");
	TObjectPtr<UEnhancedInputComponent> EIS = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind movement action to enhanced input component
	LOG("Binding move action");
	EIS->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ALab07Pawn::Move);
	
}

// Gets movement input
void ALab07Pawn::Move(const struct FInputActionInstance& Instance)
{
	// Get movement input and send to movement component
	MovementComponent->SetLastMovementInput(Instance.GetValue().Get<FVector2d>());
}

