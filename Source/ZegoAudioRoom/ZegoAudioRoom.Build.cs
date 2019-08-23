// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


using System;
using System.IO;
using UnrealBuildTool;

public class ZegoAudioRoom : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }
    private string LibPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty")); }
    }

    public string GetLibFullPath()
    {
        string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x32";
        string LibrariesPath = Path.Combine(LibPath, "lib", PlatformString);
        return LibrariesPath;
    }
    public void ReferenceDlls()
    {
        string Path = GetLibFullPath();
        var DllFiles = Directory.GetFiles(Path, "*.dll");
        foreach (var file in DllFiles)
        {
            RuntimeDependencies.Add(file);
            Console.WriteLine(file);
        }
    }
    public ZegoAudioRoom(ReadOnlyTargetRules Target) : base(Target)
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
                "ZegoAudioRoom/Private",          
                "ZegoAudioRoom/Public",
                Path.Combine(ModulePath, "Public"),
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
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        //≈‰÷√DLL
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PrivateIncludePaths.Add(Path.Combine(LibPath, "include"));
            PublicIncludePaths.Add(Path.Combine(LibPath, "Include"));

            //DLL¬∑æ∂
            string LibrariesPath = GetLibFullPath();

            PublicDelayLoadDLLs.Add("ZegoAudioRoom.dll");
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "ZegoAudioRoom.lib"));

            //“¿¿µDLL
            ReferenceDlls();
        }
    }
}
