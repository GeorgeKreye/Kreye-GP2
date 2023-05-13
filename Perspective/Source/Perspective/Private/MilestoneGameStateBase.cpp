// Fill out your copyright notice in the Description page of Project Settings.


#include "MilestoneGameStateBase.h"

#include "Perspective/Perspective.h"

AMilestoneGameStateBase::AMilestoneGameStateBase() : CurrentCamera(0)
{
	
}

// Change camera via function
void AMilestoneGameStateBase::ChangeCamera(const int NewCamera)
{
	// Make sure camera is valid
	if (NewCamera >= 0 && NewCamera < MAX_CAMERA)
	{
		CurrentCamera = NewCamera; // Will automatically change player camera and view-dependent objects
		LOG("Camera changed to camera %d", NewCamera+1);
	}
}
