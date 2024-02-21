// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#if WITH_GAMELIFT 
#include "GameLiftServerSDK.h"
#endif
#include "GameliftServerSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FExtraParametersForServerSetup
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift|Server")
	FString AuthToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift|Server")
	FString HostId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift|Server")
	FString FleetId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift|Server")
	FString WebSocketUrl;
};

UENUM(BlueprintType)
enum EPlayerAcceptancePolicy
{
	NOT_SET,
	ACCEPT_ALL,
	DENY_ALL
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameliftServerProcessReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameliftServerProcessTerminate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameliftServerHealthCheck);

UCLASS()
class GAMELIFTSERVERSDK_API UGameliftServerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit|GameLift|Server")
	void SetupGameLiftServer(int32 ServerPort, FString LogFilePath, FExtraParametersForServerSetup ExtraSettings,bool& bIsSuccess, FString& ErrorMessage);

	UFUNCTION(BlueprintPure, Category = "AWS Integration Kit|GameLift|Server")
	static int32 GetCurrentServerPort(const AGameModeBase* CurrentGameMode);
	
	UFUNCTION(BlueprintPure, Category = "AWS Integration Kit|GameLift|Server")
	static FString GetSavedFolderPath();

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit|GameLift|Server")
	bool ProcessReady();

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit|GameLift|Server")
	bool ProcessTerminate();

	UFUNCTION(BlueprintPure, Category = "AWS Integration Kit|GameLift|Server")
	static FString GetGameLiftServerSdkVersion();

	UFUNCTION(BlueprintPure, Category = "AWS Integration Kit|GameLift|Server")
	static FString GetGameSessionId();

	UFUNCTION(BlueprintPure, Category = "AWS Integration Kit|GameLift|Server")
	static float GetTerminationTime();

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit|GameLift|Server")
	bool UpdatePlayerSessionCreationPolicy(EPlayerAcceptancePolicy Policy);

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit|GameLift|Server")
	static bool AcceptPlayerSession(const FString& playerSessionId);

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit|GameLift|Server")
	static bool RemovePlayerSession(const FString& playerSessionId);

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit|GameLift|Server")
	static bool StartBackfillMatch(const FString& ticketId, const FString& gameSessionArn, const FString& matchmakingConfigurationArn, const TArray<FString>& players);

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit|GameLift|Server")
	static bool StopBackfillMatch(const FString& ticketId, const FString& gameSessionArn, const FString& matchmakingConfigurationArn);

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit|GameLift|Server")
	static bool DescribePlayerSessions(const FString& gameSessionId, const FString& playerId, const FString& playerSessionId, const FString& playerSessionStatus);
private:
	
#if WITH_GAMELIFT
	FProcessParameters m_params;
#endif
};
