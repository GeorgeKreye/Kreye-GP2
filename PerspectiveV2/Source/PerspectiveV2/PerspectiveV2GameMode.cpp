// Copyright Epic Games, Inc. All Rights Reserved.

#include "PerspectiveV2GameMode.h"
#include "PerspectiveV2Character.h"
#include "UObject/ConstructorHelpers.h"

APerspectiveV2GameMode::APerspectiveV2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
