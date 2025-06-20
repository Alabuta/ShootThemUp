// Learning project from Udemy course

using UnrealBuildTool;

public class ShootThemUp : ModuleRules
{
	public ShootThemUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange([
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"PhysicsCore",
			"Niagara",
			"GameplayTasks",
			"NavigationSystem"
		]);

		// PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange([
			"ShootThemUp/Weapon",
			"ShootThemUp/Game",
			"ShootThemUp/Player",
			"ShootThemUp/AI",
			"ShootThemUp/AI/Tasks"
		]);

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
