// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "GameliftServerSubsystem.h"

#include "GameLiftServerSDK.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "GameFramework/GameModeBase.h"


void UGameliftServerSubsystem::SetupGameLiftServer(int32 ServerPort, FString LogFilePath, FExtraParametersForServerSetup ExtraSettings,bool& bIsSuccess, FString& ErrorMessage)
{
#if WITH_GAMELIFT
	FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
	//Define the server parameters for a GameLift Anywhere fleet. These are not needed for a GameLift managed EC2 fleet.
    FServerParameters serverParameters;
    UE_LOG(LogTemp, Log, TEXT("Initializing the GameLift Server"));
    //AuthToken returned from the "aws gamelift get-compute-auth-token" API. Note this will expire and require a new call to the API after 15 minutes.
    if(ExtraSettings.AuthToken.IsEmpty())
    {
        if (FParse::Value(FCommandLine::Get(), TEXT("-authtoken="), serverParameters.m_authToken))
        {
            UE_LOG(LogTemp, Log, TEXT("AUTH_TOKEN: %s"), *serverParameters.m_authToken)
        }
    }
    else
    {
        serverParameters.m_authToken = ExtraSettings.AuthToken;
        UE_LOG(LogTemp, Log, TEXT("AUTH_TOKEN: %s"), *serverParameters.m_authToken)
    }

    if(ExtraSettings.HostId.IsEmpty())
    {
        //The Host/compute-name of the GameLift Anywhere instance.
        if (FParse::Value(FCommandLine::Get(), TEXT("-hostid="), serverParameters.m_hostId))
        {
            UE_LOG(LogTemp, Log, TEXT("HOST_ID: %s"), *serverParameters.m_hostId)
        }
    }
    else
    {
        serverParameters.m_hostId = ExtraSettings.HostId;
        UE_LOG(LogTemp, Log, TEXT("HOST_ID: %s"), *serverParameters.m_hostId)
    }

    if(ExtraSettings.FleetId.IsEmpty())
    {
        //The Anywhere Fleet ID.
        if (FParse::Value(FCommandLine::Get(), TEXT("-fleetid="), serverParameters.m_fleetId))
        {
            UE_LOG(LogTemp, Log, TEXT("FLEET_ID: %s"), *serverParameters.m_fleetId)
        }
    }
    else
    {
        serverParameters.m_fleetId = ExtraSettings.FleetId;
        UE_LOG(LogTemp, Log, TEXT("FLEET_ID: %s"), *serverParameters.m_fleetId)
    }

    if(ExtraSettings.WebSocketUrl.IsEmpty())
    {
        //The WebSocket URL (GameLiftServiceSdkEndpoint).
        if (FParse::Value(FCommandLine::Get(), TEXT("-websocketurl="), serverParameters.m_webSocketUrl))
        {
            UE_LOG(LogTemp, Log, TEXT("WEBSOCKET_URL: %s"), *serverParameters.m_webSocketUrl)
        }
    }
    else
    {
        serverParameters.m_webSocketUrl = ExtraSettings.WebSocketUrl;
        UE_LOG(LogTemp, Log, TEXT("WEBSOCKET_URL: %s"), *serverParameters.m_webSocketUrl)
    }

    //The PID of the running process
    serverParameters.m_processId = FString::Printf(TEXT("%d"), FGenericPlatformProcess::GetCurrentProcessId());
    UE_LOG(LogTemp, Log, TEXT("PID: %s"), *serverParameters.m_processId);

    //InitSDK establishes a local connection with GameLift's agent to enable further communication.
    //Use InitSDK(serverParameters) for a GameLift Anywhere fleet. 
    //Use InitSDK() for a GameLift managed EC2 fleet.
    auto GameLiftResult =  gameLiftSdkModule->InitSDK(serverParameters);
if (GameLiftResult.IsSuccess())
{
    UE_LOG(LogTemp, Log, TEXT("GameLift SDK is initialized"));
}
else
{
    UE_LOG(LogTemp, Log, TEXT("GameLift SDK failed to initialize"));
    ErrorMessage = GameLiftResult.GetError().m_errorMessage;
    bIsSuccess = false;
    return;
}
    //Implement callback function onStartGameSession
    //GameLift sends a game session activation request to the game server
    //and passes a game session object with game properties and other settings.
    //Here is where a game server takes action based on the game session object.
    //When the game server is ready to receive incoming player connections, 
    //it invokes the server SDK call ActivateGameSession().
    auto onGameSession = [=](Aws::GameLift::Server::Model::GameSession gameSession)
    {
        FString gameSessionId = FString(gameSession.GetGameSessionId());
        UE_LOG(LogTemp, Log, TEXT("GameSession Initializing: %s"), *gameSessionId);
        gameLiftSdkModule->ActivateGameSession();
        FOnGameliftServerProcessReady().Broadcast();
    };

    m_params.OnStartGameSession.BindLambda(onGameSession);

    //Implement callback function OnProcessTerminate
    //GameLift invokes this callback before shutting down the instance hosting this game server.
    //It gives the game server a chance to save its state, communicate with services, etc., 
    //and initiate shut down. When the game server is ready to shut down, it invokes the 
    //server SDK call ProcessEnding() to tell GameLift it is shutting down.
    auto onProcessTerminate = [=]() 
    {
        UE_LOG(LogTemp, Log, TEXT("Game Server Process is terminating"));
        FOnGameliftServerProcessTerminate().Broadcast();
        gameLiftSdkModule->ProcessEnding();
    };

    m_params.OnTerminate.BindLambda(onProcessTerminate);

    //Implement callback function OnHealthCheck
    //GameLift invokes this callback approximately every 60 seconds.
    //A game server might want to check the health of dependencies, etc.
    //Then it returns health status true if healthy, false otherwise.
    //The game server must respond within 60 seconds, or GameLift records 'false'.
    //In this example, the game server always reports healthy.
    auto onHealthCheck = []() 
    {
        UE_LOG(LogTemp, Log, TEXT("Performing Health Check"));
        FOnGameliftServerHealthCheck().Broadcast();
        return true;
    };

    m_params.OnHealthCheck.BindLambda(onHealthCheck);

    //The game server gets ready to report that it is ready to host game sessions
    //and that it will listen on port 7777 for incoming player connections.
    m_params.port = ServerPort;

    //Here, the game server tells GameLift where to find game session log files.
    //At the end of a game session, GameLift uploads everything in the specified 
    //location and stores it in the cloud for access later.
    TArray<FString> logfiles;
    logfiles.Add(LogFilePath);
    m_params.logParameters = logfiles;

    //The game server calls ProcessReady() to tell GameLift it's ready to host game sessions.
    UE_LOG(LogTemp, Log, TEXT("Calling Process Ready"));
    gameLiftSdkModule->ProcessReady(m_params);
    bIsSuccess = true;
    ErrorMessage = "";
#else
    bIsSuccess = false;
    ErrorMessage = "GameLift is not enabled";
#endif
}

int32 UGameliftServerSubsystem::GetCurrentServerPort(const AGameModeBase* CurrentGameMode)
{
    return CurrentGameMode->GetWorld()->URL.Port;
}

FString UGameliftServerSubsystem::GetSavedFolderPath()
{
    //Get the saved folder path
    return FPaths::ProjectSavedDir();
}

bool UGameliftServerSubsystem::ProcessReady()
{
#if WITH_GAMELIFT
    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
    if(gameLiftSdkModule->ProcessReady(m_params).IsSuccess())
    {
        return true;
    }
    else
    {
        return false;
    }
#endif
    return false;
}

bool UGameliftServerSubsystem::ProcessTerminate()
{
#if WITH_GAMELIFT
    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
    if(gameLiftSdkModule->ProcessEnding().IsSuccess())
    {
        return true;
    }
    else
    {
        return false;
    }
#endif
    return false;
}

FString UGameliftServerSubsystem::GetGameLiftServerSdkVersion()
{
#if WITH_GAMELIFT
    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
    return gameLiftSdkModule->GetVersion();
#endif
    return "";
}

FString UGameliftServerSubsystem::GetGameSessionId()
{
#if WITH_GAMELIFT
    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
    return gameLiftSdkModule->GetGameSessionId();
#endif
    return "";
}

float UGameliftServerSubsystem::GetTerminationTime()
{
#if WITH_GAMELIFT
    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
    return gameLiftSdkModule->GetTerminationTime();
#endif
    return 0.0f;
}

bool UGameliftServerSubsystem::UpdatePlayerSessionCreationPolicy(EPlayerAcceptancePolicy Policy)
{
#if WITH_GAMELIFT
    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
    if (Policy == EPlayerAcceptancePolicy::ACCEPT_ALL)
    {
        if(gameLiftSdkModule->UpdatePlayerSessionCreationPolicy(Aws::GameLift::Server::Model::PlayerSessionCreationPolicy::ACCEPT_ALL).IsSuccess())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (Policy == EPlayerAcceptancePolicy::DENY_ALL)
    {
        if(gameLiftSdkModule->UpdatePlayerSessionCreationPolicy(Aws::GameLift::Server::Model::PlayerSessionCreationPolicy::DENY_ALL).IsSuccess())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if(gameLiftSdkModule->UpdatePlayerSessionCreationPolicy(Aws::GameLift::Server::Model::PlayerSessionCreationPolicy::NOT_SET).IsSuccess())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
#endif
    return false;
}

bool UGameliftServerSubsystem::AcceptPlayerSession(const FString& playerSessionId)
{
#if WITH_GAMELIFT
    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
    if(gameLiftSdkModule->AcceptPlayerSession(TCHAR_TO_ANSI(*playerSessionId)).IsSuccess())
    {
        return true;
    }
    else
    {
        return false;
    }
#endif
    return false;
}

bool UGameliftServerSubsystem::RemovePlayerSession(const FString& playerSessionId)
{
#if WITH_GAMELIFT
    FGameLiftServerSDKModule* gameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));
    if(gameLiftSdkModule->RemovePlayerSession(TCHAR_TO_ANSI(*playerSessionId)).IsSuccess())
    {
        return true;
    }
    else
    {
        return false;
    }
#endif
    return false;
}
