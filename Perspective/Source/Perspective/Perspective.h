// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Declare log
DECLARE_LOG_CATEGORY_EXTERN(MilestoneLog, Log, All);

#define LOG(msg, ...) UE_LOG(MilestoneLog, Log, TEXT(msg), __VA_ARGS__)
#define WARN(msg, ...) UE_LOG(MilestoneLog, Warning, TEXT(msg), __VA_ARGS__)
