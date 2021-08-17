using UnrealBuildTool;
using System.IO;

public class ForestMagus : ModuleRules
{
	public ForestMagus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.Add(ModuleDirectory);

        PublicIncludePaths.Add(ModuleDirectory);

        //PublicIncludePaths.AddRange(new string[]
        //{
        //    Path.Combine(ModuleDirectory, "Strcuts"),
        //    Path.Combine(ModuleDirectory, "Content")
        //});
    }
}
