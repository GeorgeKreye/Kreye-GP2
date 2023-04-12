// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KREYE_GP2_API UCustomSceneComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomSceneComponent();

	UPROPERTY(EditAnywhere);
	AActor* Parent;

	UPROPERTY(EditAnywhere);
	TArray<AActor *> Children;

	UPROPERTY(EditAnywhere);
	FTransform LocalTransform;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TranslateTransform(const FVector LocationChange);
	void RotateTransform(const FQuat RotationChange);
	void ScaleTransform(const FVector ScaleChange);

		
};
