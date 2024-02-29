// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "StartGameSessionPlacement_Async.h"

#include "Async/Async.h"
#include "aws/gamelift/model/StartGameSessionPlacementRequest.h"

UStartGameSessionPlacement_Async* UStartGameSessionPlacement_Async::StartGameSessionPlacement(
	TArray<FDesiredPlayerSession> DesiredPlayerSessions, TArray<FGameProperty> GameProperties, FString GameSessionData,
	FString AwsGameSessionName, FString GameSessionQueueName, int32 MaxPlayerSessionCount, FString PlacementId,
	TArray<FPlayerLatency> PlayerLatencies)
{
	UStartGameSessionPlacement_Async* Obj = NewObject<UStartGameSessionPlacement_Async>();
	Obj->Var_DesiredPlayerSessions = DesiredPlayerSessions;
	Obj->Var_GameProperties = GameProperties;
	Obj->Var_GameSessionData = GameSessionData;
	Obj->Var_GameSessionName = AwsGameSessionName;
	Obj->Var_GameSessionQueueName = GameSessionQueueName;
	Obj->Var_MaxPlayerSessionCount = MaxPlayerSessionCount;
	Obj->Var_PlacementId = PlacementId;
	Obj->Var_PlayerLatencies = PlayerLatencies;
	return Obj;
}

void UStartGameSessionPlacement_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::StartGameSessionPlacementRequest Request;
	if (!Var_GameSessionQueueName.IsEmpty())
	{
		Request.SetGameSessionQueueName(TCHAR_TO_UTF8(*Var_GameSessionQueueName));
	}
	if(!Var_PlacementId.IsEmpty())
	{
		Request.SetPlacementId(TCHAR_TO_UTF8(*Var_PlacementId));
	}
	if(Var_DesiredPlayerSessions.Num() > 0)
	{
		for (auto& Local_DesiredPlayerSession : Var_DesiredPlayerSessions)
		{
			Request.AddDesiredPlayerSessions(Local_DesiredPlayerSession.ToDesiredPlayerSession());
		}
	}
	if(Var_GameProperties.Num() > 0)
	{
		for (auto& GameProperty : Var_GameProperties)
		{
			Request.AddGameProperties(GameProperty.ToGameProperty());
		}
	}
	if(!Var_GameSessionData.IsEmpty())
	{
		Request.SetGameSessionData(TCHAR_TO_UTF8(*Var_GameSessionData));
	}
	if(!Var_GameSessionName.IsEmpty())
	{
		Request.SetGameSessionName(TCHAR_TO_UTF8(*Var_GameSessionName));
	}
	if(Var_MaxPlayerSessionCount > 0)
	{
		Request.SetMaximumPlayerSessionCount(Var_MaxPlayerSessionCount);
	}
	if(Var_PlayerLatencies.Num() > 0)
	{
		for (auto& PlayerLatency : Var_PlayerLatencies)
		{
			Request.AddPlayerLatencies(PlayerLatency.ToPlayerLatency());
		}
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StartGameSessionPlacementRequest&, const Aws::GameLift::Model::StartGameSessionPlacementOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				Success.Broadcast(outcome.GetResult().GetGameSessionPlacement(), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(FGameSessionPlacement(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->StartGameSessionPlacementAsync(Request, AsyncCallback);
	
}

void UStartGameSessionPlacement_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FGameSessionPlacement(), Error);
}
