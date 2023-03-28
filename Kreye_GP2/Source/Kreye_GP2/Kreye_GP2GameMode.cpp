// Copyright Epic Games, Inc. All Rights Reserved.

#include "Kreye_GP2GameMode.h"
#include "Kreye_GP2Character.h"
#include "UObject/ConstructorHelpers.h"

AKreye_GP2GameMode::AKreye_GP2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
