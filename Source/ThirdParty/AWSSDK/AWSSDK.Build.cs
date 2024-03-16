//Copyright (c) 2024 Betide Studio. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;


public class AWSSDK : ModuleRules
{
    private List<string> WindowsLibraryNames = new List<string>()
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
        "aws-cpp-sdk-core",
        "zlib1",
        "aws-cpp-sdk-gamelift",
    };
    
    
    private List<string> LinuxLibraryNames = new List<string>()
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
        "aws-cpp-sdk-core",
        "aws-cpp-sdk-gamelift",
    };

    public AWSSDK(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnableExceptions = true;
        string ThirdPartyPath = System.IO.Path.Combine(ModuleDirectory, Target.Platform.ToString());
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
            foreach (string libName in WindowsLibraryNames)
            {
                if (libName != "zlib1")
                {
                    PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, libName + ".lib"));
                }
                RuntimeDependencies.Add(System.IO.Path.Combine(ThirdPartyPath, libName));
                RuntimeDependencies.Add(System.IO.Path.Combine(ThirdPartyPath + libName + ".dll"));
                PublicDelayLoadDLLs.Add(libName + ".dll");
            }
        }
        else if (Target.Platform == UnrealTargetPlatform.LinuxArm64 || Target.Platform == UnrealTargetPlatform.Linux) 
        {
            AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
            AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
            AddEngineThirdPartyPrivateStaticDependencies(Target, "nghttp2");
            AddEngineThirdPartyPrivateStaticDependencies(Target, "libcurl");
            foreach (var libName in LinuxLibraryNames)
            {
                string libNameWithPrefix = "lib" + libName;
                PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, libNameWithPrefix + ".a"));
            }
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            AddEngineThirdPartyPrivateStaticDependencies(Target, "nghttp2");
            AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
            AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
            AddEngineThirdPartyPrivateStaticDependencies(Target, "libcurl");
            foreach (var libName in LinuxLibraryNames)
            {
                string libNameWithPrefix = "lib" + libName;
                PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, libNameWithPrefix + ".a"));
            }
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");
            AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
            AddEngineThirdPartyPrivateStaticDependencies(Target, "libcurl");
            foreach (var libName in LinuxLibraryNames)
            {
                string libNameWithPrefix = "lib" + libName;
                PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, libNameWithPrefix + ".a"));
            }
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            foreach (var libName in LinuxLibraryNames)
            {
                string libNameWithPrefix = "lib" + libName;
                PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, libNameWithPrefix + ".a"));
            }
        }

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
            });
    }
}