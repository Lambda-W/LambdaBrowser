// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LambdaBrowser : ModuleRules
{
	public LambdaBrowser(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"InputCore",
                "Core",
                "CoreUObject",
				"Slate",
				"SlateCore",
                "WebBrowser",
                "WebBrowserWidget",
                "UMG",
                "Engine",
                "HTTP",
                }
            );

        if (Target.bBuildEditor == true)
        {
            //@TODO: UnrealEd Needed for the triangulation code used for sprites (but only in editor mode)
            //@TOOD: Try to move the code dependent on the triangulation code to the editor-only module
            PrivateIncludePathModuleNames.AddRange(
                new string[]
                {
                        "UnrealEd",
                }
            );
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                        "UnrealEd",
                }
            );
        }

        if (Target.bBuildEditor || Target.Platform == UnrealTargetPlatform.Android || Target.Platform == UnrealTargetPlatform.IOS)
        {
            // WebBrowserTexture required for cooking Android
            PrivateIncludePathModuleNames.AddRange(
                new string[]
                {
                        "WebBrowserTexture",
                }
            );
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                        "WebBrowserTexture",
                }
            );
        }


        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
