// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Declare log
DECLARE_LOG_CATEGORY_EXTERN(GP2Log, Log, All);

#define LOG(msg, ...) UE_LOG(GP2Log, Log, TEXT(msg), __VA_ARGS__)
#define WARN(msg, ...) UE_LOG(GP2Log, Warning, TEXT(msg), __VA_ARGS__)
