// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Kreye_GP2 : ModuleRules
{
	public Kreye_GP2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
