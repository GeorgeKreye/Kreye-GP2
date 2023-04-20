// Fill out your copyright notice in the Description page of Project Settings.


#include "Labs/Lab04/CustomSceneComponent.h"

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
		BaseTransform = FTransform::Identity;
		BaseTransform = GetWorldTransform() * BaseTransform;
	} else
	{
		BaseTransform = GetOwner()->GetActorTransform();
	}

	LocalTransform = BaseTransform * LocalTransform;
}	


// Called every frame
void UCustomSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Set world transform
	GetOwner()->SetActorTransform(GetWorldTransform());
}

void UCustomSceneComponent::TranslateTransform(const FVector& Translation)
{
	// Convert translation into matrix
	const FTransform TranslationMatrix = FTransform(Translation);

	LocalTransform += TranslationMatrix;
}

void UCustomSceneComponent::RotateTransform(const FQuat& RotationChange)
{
	const FTransform RotationMatrix = FTransform(RotationChange);

	LocalTransform *= RotationMatrix;
}

void UCustomSceneComponent::ScaleTransform(const FVector& ScaleChange)
{
	const FTransform ScaleMatrix = FTransform(ScaleChange);

	LocalTransform *= ScaleMatrix;
}

FTransform UCustomSceneComponent::GetWorldTransform()
{
	// Output; stores the world transform that is calculated
	FTransform WorldTransform = FTransform(LocalTransform);
	// The currently selected ancestor of this object
	AActor* Ancestor = Parent;

	// Loop through all ancestors
	while (Ancestor != nullptr)
	{
		// Storage for next ancestor
		TArray<UCustomSceneComponent*> Next;

		// Get next ancestor
		Ancestor->GetComponents<UCustomSceneComponent>(Next,false);
		
		// Combine transforms
		WorldTransform = WorldTransform * Next[0]->LocalTransform;
		
		// Go to ancestor
		Ancestor = Next[0]->Parent;
	}

	// Return final world transform
	return WorldTransform;
}