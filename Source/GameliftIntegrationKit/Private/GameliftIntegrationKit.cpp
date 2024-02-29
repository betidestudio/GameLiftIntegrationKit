// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GameliftIntegrationKit.h"

#include "HAL/FileManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "ThirdParty/AWSSDK/Include/aws/core/Aws.h"
#include "ThirdParty/AWSSDK/Include/aws/core/utils/logging/LogLevel.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#endif

#define LOCTEXT_NAMESPACE "FGameliftIntegrationKitModule"

void FGameliftIntegrationKitModule::StartupModule()
{
#if PLATFORM_WINDOWS
	if(const TSharedPtr<IPlugin> PluginPtr = IPluginManager::Get().FindPlugin("GameliftIntegrationKit"))
	{
		const FString PluginDir = PluginPtr->GetBaseDir();
		const FString BinDir =  FPaths::ConvertRelativePathToFull(FPaths::Combine(PluginDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("AWSSDK"), TEXT("Binaries"), TEXT("Win64")));
		FPlatformProcess::PushDllDirectory(*BinDir);
		TArray<FString> LibFiles;
		IFileManager::Get().FindFiles(LibFiles, *(BinDir / TEXT("*.dll")), true, false);
		for (auto Element : LibFiles)
		{
			const FString FinalPath = FPaths::Combine(BinDir, Element);
			DynamicLibHandles.Add(FPlatformProcess::GetDllHandle(*FinalPath));
		}
		FPlatformProcess::PopDllDirectory(*BinDir);
	}
#endif
}

void FGameliftIntegrationKitModule::ShutdownModule()
{
#if PLATFORM_WINDOWS
	for(void*& Handle : DynamicLibHandles)
	{
		if (Handle != nullptr)
		{
			FPlatformProcess::FreeDllHandle(Handle);
			Handle = nullptr;
		}
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameliftIntegrationKitModule, GameliftIntegrationKit)