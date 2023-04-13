// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab04/CustomSceneComponent.h"

#include "AnimEncoding.h"
#include "BaseGizmos/TransformSources.h"
#include "EnvironmentQuery/EnvQueryTypes.h"

// Sets default values for this component's properties
UCustomSceneComponent::UCustomSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCustomSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize local transform
	FTransform BaseTransform;
	if (Parent != nullptr)
	{
		BaseTransform = Parent->GetTransform();
	} else
	{
		BaseTransform = GetOwner()->GetTransform();
	}

	LocalTransform += BaseTransform;
}	


// Called every frame
void UCustomSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Update child transforms
	for (int i = 0; i < Children.Num(); i++)
	{
		
	}
}

void UCustomSceneComponent::TranslateTransform(const FVector& Translation)
{
	LocalTransform.SetLocation(LocalTransform.GetLocation() + Translation);
}

void UCustomSceneComponent::RotateTransform(const FQuat& RotationChange)
{
	LocalTransform.SetRotation(LocalTransform.GetRotation() + RotationChange);
}

void UCustomSceneComponent::ScaleTransform(const FVector& ScaleChange)
{
	LocalTransform.SetScale3D(LocalTransform.GetScale3D() + ScaleChange);
}
