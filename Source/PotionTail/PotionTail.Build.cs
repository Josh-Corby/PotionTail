// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PotionTail : ModuleRules
{
	public PotionTail(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"});

		PrivateDependencyModuleNames.AddRange(new string[] { "CommonUI" });
	}
}