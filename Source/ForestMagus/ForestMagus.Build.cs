using UnrealBuildTool;
using System.IO;

public class ForestMagus : ModuleRules
{
	public ForestMagus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory,"Private")
        });

        PublicIncludePaths.AddRange(new string[]
        {
            Path.Combine(ModuleDirectory, "Public"),
            Path.Combine(ModuleDirectory, "Public/PlayerCharacter"),
            Path.Combine(ModuleDirectory, "Public/GameMode")
        });
    }
}
