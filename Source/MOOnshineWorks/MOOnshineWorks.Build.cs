// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MOOnshineWorks : ModuleRules
{
	public MOOnshineWorks(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "Core", "CoreUObject", "Engine", "InputCore" });
        PublicIncludePaths.AddRange(new string[] {  "Levels" });
	}
}
