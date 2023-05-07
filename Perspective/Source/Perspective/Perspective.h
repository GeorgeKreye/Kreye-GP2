// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Declare logs
DECLARE_LOG_CATEGORY_EXTERN(MilestoneLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(GameplayLog, Log, All);

// Specify MilestoneLog functions
#define LOG(msg, ...) UE_LOG(MilestoneLog, Log, TEXT(msg), __VA_ARGS__)
#define WARN(msg, ...) UE_LOG(MilestoneLog, Warning, TEXT(msg), __VA_ARGS__)
#define ERR(msg, ...) UE_LOG(MilestoneLog, Error, TEXT(msg), __VA_ARGS__)

// Specify GameplayLog function
#define LOG_G(msg, ...) UE_LOG(GameplayLog, Log, TEXT(msg), __VA_ARGS__)