//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "aws/gamelift/model/DesiredPlayerSession.h"
#include "aws/gamelift/model/MatchmakingConfiguration.h"
#include "aws/gamelift/model/MatchmakingRuleSet.h"
#include "aws/gamelift/model/PlayerSession.h"
#include "aws/gamelift/model/GameSession.h"
#include "aws/gamelift/model/PlayerLatency.h"
#include "aws/gamelift/model/PlacedPlayerSession.h"
#include "aws/gamelift/model/GameSessionPlacement.h"
#include "aws/gamelift/model/GameSessionDetail.h"
#include "aws/gamelift/model/MatchmakingTicket.h"
#include "UObject/Object.h"
#include "GameliftSharedClass.generated.h"

//ENUMS
UENUM(BlueprintType)
enum EBackfillMode
{
	NOT_SET,
	AUTOMATIC,
	MANUAL
  };

UENUM(BlueprintType)
enum EFlexMatchMode
{
	NOT_SET1 UMETA(DisplayName = "NOT_SET"),
	STANDALONE,
	WITH_QUEUE
  };

UENUM(BlueprintType)
enum EMatchmakingConfigurationStatus
{
	NOT_SET2 UMETA(DisplayName = "NOT_SET"),
	CANCELLED,
	COMPLETED,
	FAILED,
	PLACING,
	QUEUED,
	REQUIRES_ACCEPTANCE,
	SEARCHING,
	TIMED_OUT
  };

UENUM(BlueprintType)
enum EGameSessionStatus
{
	NOT_SET3 UMETA(DisplayName = "NOT_SET"),
	ACTIVE,
	ACTIVATING,
	TERMINATED,
	TERMINATING,
	ERROR_
  };

UENUM(BlueprintType)
enum EPlayerSessionStatus
{
	NOT_SET7 UMETA(DisplayName = "NOT_SET"),
	RESERVED,
	ACTIVE1 UMETA(DisplayName = "ACTIVE"),
	COMPLETED1 UMETA(DisplayName = "COMPLETED"),
	TIMEDOUT
  };

UENUM(BlueprintType)
enum EGameSessionStatusReason
{
	NOT_SET5 UMETA(DisplayName = "NOT_SET"),
	INTERRUPTED
  };

UENUM(BlueprintType)
enum EAcceptanceType
{
	NOT_SET4 UMETA(DisplayName = "NOT_SET"),
	ACCEPT,
	REJECT
  };

UENUM(BlueprintType)
enum EPlayerSessionCreationPolicy
{
	NOT_SET6 UMETA(DisplayName = "NOT_SET"),
	ACCEPT_ALL,
	DENY_ALL
  };

UENUM(BlueprintType)
enum EGameSessionPlacementState
{
	NOT_SET8 UMETA(DisplayName = "NOT_SET"),
	PENDING,
	FULFILLED,
	CANCELLED2 UMETA(DisplayName = "CANCELLED"),
	TIMED_OUT2 UMETA(DisplayName = "TIMED_OUT"),
	FAILED2 UMETA(DisplayName = "FAILED")
  };

UENUM(BlueprintType)
enum EProtectionPolicy
{
	NOT_SET9 UMETA(DisplayName = "NOT_SET"),
	NoProtection,
	FullProtection
  };



//STRUCTS
USTRUCT(BlueprintType)
struct FGameProperty
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Key = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Value = "";

	FGameProperty(){}
	FGameProperty(const Aws::GameLift::Model::GameProperty& GameProperty)
	{
		Key = GameProperty.GetKey().c_str();
		Value = GameProperty.GetValue().c_str();
	}
	Aws::GameLift::Model::GameProperty ToGameProperty() const
	{
		Aws::GameLift::Model::GameProperty GameProperty;
		GameProperty.SetKey(TCHAR_TO_UTF8(*Key));
		GameProperty.SetValue(TCHAR_TO_UTF8(*Value));
		return GameProperty;
	}
	
};



USTRUCT(BlueprintType)
struct FMatchmakingConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Name = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Description = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FString> GameSessionQueueArns = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 RequestTimeoutSeconds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 AcceptanceTimeoutSeconds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	bool AcceptanceRequired = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString RuleSetName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString NotificationTarget = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 AdditionalPlayerCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString CustomEventData = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FGameProperty> GameProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionData = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EBackfillMode> BackfillMode = EBackfillMode::NOT_SET;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EFlexMatchMode> FlexMatchMode = EFlexMatchMode::NOT_SET1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime CreationTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime LastUpdatedTime = FDateTime::Now();

	FMatchmakingConfiguration(){}

	FMatchmakingConfiguration(const Aws::GameLift::Model::MatchmakingConfiguration& MatchmakingConfiguration)
	{
		Name = MatchmakingConfiguration.GetName().c_str();
		Description = MatchmakingConfiguration.GetDescription().c_str();
		for (auto GameSessionQueueArn : MatchmakingConfiguration.GetGameSessionQueueArns())
		{
			GameSessionQueueArns.Add(GameSessionQueueArn.c_str());
		}
		RequestTimeoutSeconds = MatchmakingConfiguration.GetRequestTimeoutSeconds();
		AcceptanceTimeoutSeconds = MatchmakingConfiguration.GetAcceptanceTimeoutSeconds();
		AcceptanceRequired = MatchmakingConfiguration.GetAcceptanceRequired();
		RuleSetName = MatchmakingConfiguration.GetRuleSetName().c_str();
		NotificationTarget = MatchmakingConfiguration.GetNotificationTarget().c_str();
		AdditionalPlayerCount = MatchmakingConfiguration.GetAdditionalPlayerCount();
		CustomEventData = MatchmakingConfiguration.GetCustomEventData().c_str();
		for (auto GameProperty : MatchmakingConfiguration.GetGameProperties())
		{
			GameProperties.Add(FGameProperty(GameProperty));
		}
		GameSessionData = MatchmakingConfiguration.GetGameSessionData().c_str();
		BackfillMode = static_cast<EBackfillMode>(MatchmakingConfiguration.GetBackfillMode());
		FlexMatchMode = static_cast<EFlexMatchMode>(MatchmakingConfiguration.GetFlexMatchMode());
		CreationTime = FDateTime(1970,1,1) + FTimespan(MatchmakingConfiguration.GetCreationTime().Millis() * ETimespan::TicksPerMillisecond);
		for (auto GameSessionQueueArn : MatchmakingConfiguration.GetGameSessionQueueArns())
		{
			GameSessionQueueArns.Add(GameSessionQueueArn.c_str());
		}
	}
	
};




USTRUCT(BlueprintType)
struct FMatchmakingRuleSet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString RuleSetName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString RuleSetArn = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString RuleSetBody = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime CreationTime = FDateTime::Now();
	

	FMatchmakingRuleSet(){}

	FMatchmakingRuleSet(const Aws::GameLift::Model::MatchmakingRuleSet& MatchmakingRuleSet)
	{
		RuleSetName = MatchmakingRuleSet.GetRuleSetName().c_str();
		RuleSetArn = MatchmakingRuleSet.GetRuleSetArn().c_str();
		RuleSetBody = MatchmakingRuleSet.GetRuleSetBody().c_str();
		CreationTime = FDateTime(1970,1,1) + FTimespan(MatchmakingRuleSet.GetCreationTime().Millis() * ETimespan::TicksPerMillisecond);
	}
	
};

USTRUCT(BlueprintType)
struct FPlayerSession
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerSessionId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString FleetId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString FleetArn = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime CreationTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime TerminationTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString IpAddress = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 Port = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerData = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EPlayerSessionStatus> Status = EPlayerSessionStatus::NOT_SET7;

	FPlayerSession(){}
	FPlayerSession(const Aws::GameLift::Model::PlayerSession& PlayerSession)
	{
		PlayerSessionId = PlayerSession.GetPlayerSessionId().c_str();
		PlayerId = PlayerSession.GetPlayerId().c_str();
		GameSessionId = PlayerSession.GetGameSessionId().c_str();
		FleetId = PlayerSession.GetFleetId().c_str();
		FleetArn = PlayerSession.GetFleetArn().c_str();
		CreationTime = FDateTime(1970,1,1) + FTimespan(PlayerSession.GetCreationTime().Millis() * ETimespan::TicksPerMillisecond);
		TerminationTime = FDateTime(1970,1,1) + FTimespan(PlayerSession.GetTerminationTime().Millis() * ETimespan::TicksPerMillisecond);
		IpAddress = PlayerSession.GetIpAddress().c_str();
		Port = PlayerSession.GetPort();
		PlayerData = PlayerSession.GetPlayerData().c_str();
		Status = static_cast<EPlayerSessionStatus>(PlayerSession.GetStatus());
	}
	
};


USTRUCT(BlueprintType)
struct FMatchedPlayerSession
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerSessionId = "";
	
	FMatchedPlayerSession(){}
	FMatchedPlayerSession(const Aws::GameLift::Model::MatchedPlayerSession& MatchedPlayerSession)
	{
		PlayerId = MatchedPlayerSession.GetPlayerId().c_str();
		PlayerSessionId = MatchedPlayerSession.GetPlayerSessionId().c_str();
	}
	
};

USTRUCT(BlueprintType)
struct FGameSessionConnectionInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString IpAddress = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 Port = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FMatchedPlayerSession> MatchedPlayerSessions = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString DnsName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionArn = "";

	FGameSessionConnectionInfo(){}
	FGameSessionConnectionInfo(const Aws::GameLift::Model::GameSessionConnectionInfo& GameSessionConnectionInfo)
	{
		IpAddress = GameSessionConnectionInfo.GetIpAddress().c_str();
		Port = GameSessionConnectionInfo.GetPort();
		DnsName = GameSessionConnectionInfo.GetDnsName().c_str();
		GameSessionArn = GameSessionConnectionInfo.GetGameSessionArn().c_str();
		for (auto MatchedPlayerSession : GameSessionConnectionInfo.GetMatchedPlayerSessions())
		{
			MatchedPlayerSessions.Add(FMatchedPlayerSession(MatchedPlayerSession));
		}
	}
};

USTRUCT(BlueprintType)
struct FDesiredPlayerSession
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerData = "";

	FDesiredPlayerSession(){}
	FDesiredPlayerSession(const Aws::GameLift::Model::DesiredPlayerSession& DesiredPlayerSession)
	{
		PlayerId = DesiredPlayerSession.GetPlayerId().c_str();
		PlayerData = DesiredPlayerSession.GetPlayerData().c_str();
	}
	Aws::GameLift::Model::DesiredPlayerSession ToDesiredPlayerSession() const
	{
		Aws::GameLift::Model::DesiredPlayerSession DesiredPlayerSession;
		DesiredPlayerSession.SetPlayerId(TCHAR_TO_UTF8(*PlayerId));
		DesiredPlayerSession.SetPlayerData(TCHAR_TO_UTF8(*PlayerData));
		return DesiredPlayerSession;
	}
	
};


USTRUCT(BlueprintType)
struct FGLGameSession
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString FleetId = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString FleetArn = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime CreationTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime TerminationTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 CurrentPlayerSessionCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 MaximumPlayerSessionCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EGameSessionStatus> Status = EGameSessionStatus::NOT_SET3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EGameSessionStatusReason> StatusReason = EGameSessionStatusReason::NOT_SET5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FGameProperty> GameProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString IpAddress = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 Port = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EPlayerSessionCreationPolicy> PlayerSessionCreationPolicy = EPlayerSessionCreationPolicy::NOT_SET6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString CreatorId = "";


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionData = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Location = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString DnsName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString MatchmakerData = "";



	FGLGameSession(){}
	FGLGameSession(const Aws::GameLift::Model::GameSession& GameSession)
	{
		GameSessionId = GameSession.GetGameSessionId().c_str();
		Name = GameSession.GetName().c_str();
		FleetId = GameSession.GetFleetId().c_str();
		FleetArn = GameSession.GetFleetArn().c_str();
		CreationTime = FDateTime(1970,1,1) + FTimespan(GameSession.GetCreationTime().Millis() * ETimespan::TicksPerMillisecond);
		TerminationTime = FDateTime(1970,1,1) + FTimespan(GameSession.GetTerminationTime().Millis() * ETimespan::TicksPerMillisecond);
		CurrentPlayerSessionCount = GameSession.GetCurrentPlayerSessionCount();
		MaximumPlayerSessionCount = GameSession.GetMaximumPlayerSessionCount();
		Status = static_cast<EGameSessionStatus>(GameSession.GetStatus());
		StatusReason = static_cast<EGameSessionStatusReason>(GameSession.GetStatusReason());
		for (auto GameProperty : GameSession.GetGameProperties())
		{
			GameProperties.Add(FGameProperty(GameProperty));
		}
		IpAddress = GameSession.GetIpAddress().c_str();
		Port = GameSession.GetPort();
		PlayerSessionCreationPolicy = static_cast<EPlayerSessionCreationPolicy>(GameSession.GetPlayerSessionCreationPolicy());
		CreatorId = GameSession.GetCreatorId().c_str();
		GameSessionData = GameSession.GetGameSessionData().c_str();
		Location = GameSession.GetLocation().c_str();
		DnsName = GameSession.GetDnsName().c_str();
		MatchmakerData = GameSession.GetMatchmakerData().c_str();
	}
	
};


USTRUCT(BlueprintType)
struct FMatchmakingTicket
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString TicketId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString ConfigurationName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EMatchmakingConfigurationStatus> Status = EMatchmakingConfigurationStatus::NOT_SET2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString StatusReason = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString StatusMessage = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString StatusDetails = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FGameSessionConnectionInfo GameSessionConnectionInfo = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 EstimatedWaitTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString MatchmakingConfigurationArn = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Players = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime StartTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime EndTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime CreationTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime LastUpdatedTime = FDateTime::Now();

	FMatchmakingTicket(){}

	FMatchmakingTicket(const Aws::GameLift::Model::MatchmakingTicket& MatchmakingTicket)
	{
		TicketId = MatchmakingTicket.GetTicketId().c_str();
		ConfigurationName = MatchmakingTicket.GetConfigurationName().c_str();
		Status = static_cast<EMatchmakingConfigurationStatus>(MatchmakingTicket.GetStatus());
		StatusReason = MatchmakingTicket.GetStatusReason().c_str();
		StatusMessage = MatchmakingTicket.GetStatusMessage().c_str();
		GameSessionConnectionInfo = MatchmakingTicket.GetGameSessionConnectionInfo();
		EstimatedWaitTime = MatchmakingTicket.GetEstimatedWaitTime();
	}
};

USTRUCT(BlueprintType)
struct FPlayerLatency
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString RegionIdentifier = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 LatencyInMilliseconds = 0;

	FPlayerLatency(){}
	FPlayerLatency(const Aws::GameLift::Model::PlayerLatency& PlayerLatency)
	{
		PlayerId = PlayerLatency.GetPlayerId().c_str();
		RegionIdentifier = PlayerLatency.GetRegionIdentifier().c_str();
		LatencyInMilliseconds = PlayerLatency.GetLatencyInMilliseconds();
	}
	Aws::GameLift::Model::PlayerLatency ToPlayerLatency() const
	{
		Aws::GameLift::Model::PlayerLatency PlayerLatency;
		PlayerLatency.SetPlayerId(TCHAR_TO_UTF8(*PlayerId));
		PlayerLatency.SetRegionIdentifier(TCHAR_TO_UTF8(*RegionIdentifier));
		PlayerLatency.SetLatencyInMilliseconds(LatencyInMilliseconds);
		return PlayerLatency;
	}
};

USTRUCT(BlueprintType)
struct FAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString S = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	float N = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FString> SL = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TMap<FString, float> SDM = {};

	FAttributeValue (){}
	FAttributeValue (const Aws::GameLift::Model::AttributeValue& AttributeValue)
	{
		S = AttributeValue.GetS().c_str();
		N = AttributeValue.GetN();
		for (auto S1 : AttributeValue.GetSL())
		{
			SL.Add(S1.c_str());
		}
		for (auto SDM1 : AttributeValue.GetSDM())
		{
			SDM.Add(SDM1.first.c_str(), SDM1.second);
		}
	}
	Aws::GameLift::Model::AttributeValue ToAttributeValue() const
	{
		Aws::GameLift::Model::AttributeValue AttributeValue;
		AttributeValue.SetS(TCHAR_TO_UTF8(*S));
		AttributeValue.SetN(N);
		for (auto S1 : SL)
		{
			AttributeValue.AddSL(TCHAR_TO_UTF8(*S1));
		}
		for (auto SDM1 : SDM)
		{
			AttributeValue.AddSDM(TCHAR_TO_UTF8(*SDM1.Key), SDM1.Value);
		}
		return AttributeValue;
	}
	
};

USTRUCT(BlueprintType)
struct FGameliftPlayer
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TMap<FString, int32> LatenctyInMs = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TMap<FString, FAttributeValue> PlayerAttributes = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Team = "";

	FGameliftPlayer(){}
	FGameliftPlayer(const Aws::GameLift::Model::Player& Player)
	{
		for (auto LatencyInMs1 : Player.GetLatencyInMs())
		{
			LatenctyInMs.Add(LatencyInMs1.first.c_str(), LatencyInMs1.second);
		}
		for (auto PlayerAttribute : Player.GetPlayerAttributes())
		{
			PlayerAttributes.Add(PlayerAttribute.first.c_str(), FAttributeValue(PlayerAttribute.second));
		}
		PlayerId = Player.GetPlayerId().c_str();
		Team = Player.GetTeam().c_str();
	}
	Aws::GameLift::Model::Player ToGameliftPlayer() const
	{
		Aws::GameLift::Model::Player Player;
		for (auto LatencyInMs1 : LatenctyInMs)
		{
			Player.AddLatencyInMs(TCHAR_TO_UTF8(*LatencyInMs1.Key), LatencyInMs1.Value);
		}
		for (auto PlayerAttribute : PlayerAttributes)
		{
			Player.AddPlayerAttributes(TCHAR_TO_UTF8(*PlayerAttribute.Key), PlayerAttribute.Value.ToAttributeValue());
		}
		Player.SetPlayerId(TCHAR_TO_UTF8(*PlayerId));
		Player.SetTeam(TCHAR_TO_UTF8(*Team));
		return Player;
	}
};

USTRUCT(BlueprintType)
struct FPlacedPlayerSession
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlayerSessionId = "";

	FPlacedPlayerSession(){}
	FPlacedPlayerSession(const Aws::GameLift::Model::PlacedPlayerSession& PlacedPlayerSession)
	{
		PlayerId = PlacedPlayerSession.GetPlayerId().c_str();
		PlayerSessionId = PlacedPlayerSession.GetPlayerSessionId().c_str();
	}
	
};

USTRUCT(BlueprintType)
struct FGameSessionPlacement
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString DnsName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime EndTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FGameProperty> GameProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionArn = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionData = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionQueueName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionRegion = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString IpAddress = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString MatchmakerData = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 MaximumPlayerSessionCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FPlacedPlayerSession> PlacedPlayerSessions = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString PlacementId = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FPlayerLatency> PlayerLatencies = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 Port = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FDateTime StartTime = FDateTime::Now();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EGameSessionPlacementState> Status = EGameSessionPlacementState::NOT_SET8;

	FGameSessionPlacement(){}
	FGameSessionPlacement(const Aws::GameLift::Model::GameSessionPlacement& GameSessionPlacement)
	{
		DnsName = GameSessionPlacement.GetDnsName().c_str();
		EndTime = FDateTime(1970,1,1) + FTimespan(GameSessionPlacement.GetEndTime().Millis() * ETimespan::TicksPerMillisecond);
		for (auto GameProperty : GameSessionPlacement.GetGameProperties())
		{
			GameProperties.Add(FGameProperty(GameProperty));
		}
		GameSessionArn = GameSessionPlacement.GetGameSessionArn().c_str();
		GameSessionData = GameSessionPlacement.GetGameSessionData().c_str();
		GameSessionId = GameSessionPlacement.GetGameSessionId().c_str();
		GameSessionName = GameSessionPlacement.GetGameSessionName().c_str();
		GameSessionQueueName = GameSessionPlacement.GetGameSessionQueueName().c_str();
		GameSessionRegion = GameSessionPlacement.GetGameSessionRegion().c_str();
		IpAddress = GameSessionPlacement.GetIpAddress().c_str();
		MatchmakerData = GameSessionPlacement.GetMatchmakerData().c_str();
		MaximumPlayerSessionCount = GameSessionPlacement.GetMaximumPlayerSessionCount();
		for (auto PlacedPlayerSession : GameSessionPlacement.GetPlacedPlayerSessions())
		{
			PlacedPlayerSessions.Add(FPlacedPlayerSession(PlacedPlayerSession));
		}
		PlacementId = GameSessionPlacement.GetPlacementId().c_str();
		for (auto PlayerLatency : GameSessionPlacement.GetPlayerLatencies())
		{
			PlayerLatencies.Add(FPlayerLatency(PlayerLatency));
		}
		Port = GameSessionPlacement.GetPort();
		StartTime = FDateTime(1970,1,1) + FTimespan(GameSessionPlacement.GetStartTime().Millis() * ETimespan::TicksPerMillisecond);
		Status = static_cast<EGameSessionPlacementState>(GameSessionPlacement.GetStatus());
	}	
};


USTRUCT(BlueprintType)
struct FGameSessionDetail
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FGLGameSession GameSession = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EProtectionPolicy> ProtectionPolicy = EProtectionPolicy::NOT_SET9;

	FGameSessionDetail(){}

	FGameSessionDetail(const Aws::GameLift::Model::GameSessionDetail& GameSessionDetail)
	{
		GameSession = FGLGameSession(GameSessionDetail.GetGameSession());
		ProtectionPolicy = static_cast<EProtectionPolicy>(GameSessionDetail.GetProtectionPolicy());
	}
	
};


/**
 * 
 */
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UGameliftSharedClass : public UObject
{
	GENERATED_BODY()
	
};
