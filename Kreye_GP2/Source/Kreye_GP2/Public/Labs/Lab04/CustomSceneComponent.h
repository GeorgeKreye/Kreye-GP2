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

	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	FTransform LocalTransform;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// UFUNCTION(BlueprintCallable, Category = "Transforms");
	// TODO: Figure out why this UFUNCTION declaration is not working
	void TranslateTransform(const FVector& Translation);

	// UFUNCTION(BlueprintCallable, Category = "Transforms");
	// TODO: Figure out why this UFUNCTION declaration is not working
	void RotateTransform(const FQuat& RotationChange);

	// UFUNCTION(BlueprintCallable, Category = "Transforms");
	// TODO: Figure out why this UFUNCTION declaration is not working
	void ScaleTransform(const FVector& ScaleChange);

	/**
	 * @brief Gets the world transform of this object
	 * @return The world transform
	 */
	FTransform GetWorldTransform();
};
