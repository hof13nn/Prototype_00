// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Prototype_00 : ModuleRules
{
	public Prototype_00(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "GameplayTasks", "UMG", "GameplayTags"  });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[]
		{
			"Prototype_00/Public/Actions",
			"Prototype_00/Public/AI",
			"Prototype_00/Public/AI/Services",
			"Prototype_00/Public/AI/Tasks",
			"Prototype_00/Public/Base",
			"Prototype_00/Public/Base/Actions",
			"Prototype_00/Public/Base/Actors",
			"Prototype_00/Public/Base/Components",
			"Prototype_00/Public/Components",
			"Prototype_00/Public/Environment",
			"Prototype_00/Public/Environment/Objects",
			"Prototype_00/Public/Components/Controller",
			"Prototype_00/Public/Components/Player",
			"Prototype_00/Public/Core",
			"Prototype_00/Public/Environment",
			"Prototype_00/Public/Environment/Objects",
			"Prototype_00/Public/Input",
			"Prototype_00/Public/Interfaces",
			"Prototype_00/Public/Libraries",
			"Prototype_00/Public/Player",
			"Prototype_00/Public/UI",
		});
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
