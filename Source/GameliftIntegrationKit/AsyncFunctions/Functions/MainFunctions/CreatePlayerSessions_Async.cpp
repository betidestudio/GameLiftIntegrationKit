// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "CreatePlayerSessions_Async.h"

#include "Async.h"
#include "aws/gamelift/model/CreatePlayerSessionsRequest.h"

UCreatePlayerSessions_Async* UCreatePlayerSessions_Async::CreatePlayerSessions(FString GameSessionId,
                                                                               TArray<FString> PlayerIds, TMap<FString, FString> PlayerDataMap)
{
	UCreatePlayerSessions_Async* Obj = NewObject<UCreatePlayerSessions_Async>();
	Obj->Var_GameSessionId = GameSessionId;
	Obj->Var_PlayerIds = PlayerIds;
	Obj->Var_PlayerDataMap = PlayerDataMap;
	return Obj;
}

void UCreatePlayerSessions_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::CreatePlayerSessionsRequest GameLiftRequest;
	GameLiftRequest.SetGameSessionId(TCHAR_TO_UTF8(*Var_GameSessionId));
	for (FString PlayerId : Var_PlayerIds)
	{
		GameLiftRequest.AddPlayerIds(TCHAR_TO_UTF8(*PlayerId));
	}
	for (auto& Elem : Var_PlayerDataMap)
	{
		GameLiftRequest.AddPlayerDataMap(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreatePlayerSessionsRequest&, const Aws::GameLift::Model::CreatePlayerSessionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				TArray<FPlayerSession> PlayerSessions;
				for (auto PlayerSession : outcome.GetResult().GetPlayerSessions())
				{
					PlayerSessions.Add(FPlayerSession(PlayerSession));
				}
				Success.Broadcast(PlayerSessions, FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(TArray<FPlayerSession>(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->CreatePlayerSessionsAsync(GameLiftRequest, AsyncCallback);
}

void UCreatePlayerSessions_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(TArray<FPlayerSession>(), Error);
}
