// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MOOnshineWorks : ModuleRules
{
	public MOOnshineWorks(TargetInfo Target)
	{

        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Sockets", "Networking", "AIModule" });

        PublicIncludePaths.AddRange(new string[] {  "AI", "Menu", "Network", "Pickups", "Weapons" });

        //PrivateDependencyModuleNames.AddRange(new string[] { "Sockets", "Networking" });
	}
}
