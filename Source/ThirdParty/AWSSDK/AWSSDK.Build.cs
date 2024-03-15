//Copyright (c) 2024 Betide Studio. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;


public class AWSSDK : ModuleRules
{
    private List<string> LibraryNames = new List<string>()
    {
        "aws-c-sdkutils",
        "aws-c-auth",
        "aws-c-cal",
        "aws-c-compression",
        "aws-c-http",
        "aws-c-io",
        "aws-c-mqtt",
        "aws-c-s3",
        "aws-c-common",
        "aws-checksums",
        "aws-c-event-stream",
        "aws-crt-cpp",
    };

    public AWSSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableExceptions = true;

        // add the header files for reference
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Include"));
        bEnableUndefinedIdentifierWarnings = false;
        PublicDefinitions.Add("USE_IMPORT_EXPORT");
        PublicDefinitions.Add("AWS_CRT_CPP_USE_IMPORT_EXPORT");
        PublicDefinitions.Add("AWS_USE_IO_COMPLETION_PORTS");
        PublicDefinitions.Add("AWS_DEEP_CHECKS=1");

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDefinitions.Add("USE_WINDOWS_DLL_SEMANTICS");
        }
        foreach (string libName in LibraryNames)
        {
            string LibraryPath = Path.Combine(ModuleDirectory, "Binaries", Target.Platform.ToString());
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, libName + ".lib"));
                RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/AWSSDK/Binaries/Win64/" + libName + ".dll");
                PublicDelayLoadDLLs.Add(libName + ".dll");
            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
                
            }
            else if (Target.Platform == UnrealTargetPlatform.Linux)
            {
                
            }
        }

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string LibraryPath = Path.Combine(ModuleDirectory, "Binaries", Target.Platform.ToString());
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(LibraryPath, "aws-cpp-sdk-core.lib"));
            PublicDelayLoadDLLs.Add("aws-cpp-sdk-core.dll");
            string sdkLibWindows = System.IO.Path.Combine(LibraryPath, "aws-cpp-sdk-core.dll");
            RuntimeDependencies.Add(System.IO.Path.Combine(LibraryPath, "aws-cpp-sdk-core.dll"));
            
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/AWSSDK/Binaries/Win64/" + "zlib1" + ".dll");
            PublicDelayLoadDLLs.Add("zlib1" + ".dll");
                
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(LibraryPath, "aws-cpp-sdk-gamelift.lib"));
            PublicDelayLoadDLLs.Add("aws-cpp-sdk-gamelift.dll");
            RuntimeDependencies.Add(System.IO.Path.Combine(LibraryPath, "aws-cpp-sdk-gamelift.dll"));
        }

        PrivateDependencyModuleNames.AddRange(
        new string[] {
                    "CoreUObject",
                    "Engine",
                    "Slate",
                    "SlateCore",   
        });
    }
}