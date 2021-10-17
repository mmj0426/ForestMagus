//copyright @¹ÎÁö

using UnrealBuildTool;
using System.IO;

public class ForestMagus : ModuleRules
{
	public ForestMagus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AIModule", "NavigationSystem" });

        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });

        PrivateIncludePaths.Add(ModuleDirectory);

        PublicIncludePaths.Add(ModuleDirectory);

        //PublicIncludePaths.AddRange(new string[]
        //{
        //    Path.Combine(ModuleDirectory, "Strcuts"),
        //    Path.Combine(ModuleDirectory, "Content")
        //});
    }
}
