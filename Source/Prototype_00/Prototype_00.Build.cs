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
			"Prototype_00/Public/AI/Tasks",
			"Prototype_00/Public/AI/Services",
			"Prototype_00/Public/Base",
			"Prototype_00/Public/Base/Actions",
			"Prototype_00/Public/Base/Actors",
			"Prototype_00/Public/Base/Components",
			// "ActionRogueLike/Public/Base/Items",
			"Prototype_00/Public/Components",
			// "ActionRogueLike/Public/Components/PlayerController",
			"Prototype_00/Public/Components/Player",
			// "ActionRogueLike/Public/Components/Weapon",
			"Prototype_00/Public/Core",
			// "ActionRogueLike/Public/Effects",
			// "ActionRogueLike/Public/Effects/Buffs",
			// "ActionRogueLike/Public/Effects/Debuffs",
			"Prototype_00/Public/Environment",
			"Prototype_00/Public/Environment/Objects",
			"Prototype_00/Public/Input",
			"Prototype_00/Public/Interfaces",
			// "ActionRogueLike/Public/Items",
			// "ActionRogueLike/Public/Items/Pickups",
			"Prototype_00/Public/Libraries",
			//"ActionRogueLike/Public/Misc",
			"Prototype_00/Public/Player",
			//"ActionRogueLike/Public/Projectiles",
			"Prototype_00/Public/UI",
			// "ActionRogueLike/Public/UI/Objects",
			// "ActionRogueLike/Public/Weapons"
		});
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
