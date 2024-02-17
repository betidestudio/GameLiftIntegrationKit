// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "DescribePlayerSessions_Async.h"

#include "Async.h"
#include "aws/gamelift/model/DescribePlayerSessionsRequest.h"

UDescribePlayerSessions_Async* UDescribePlayerSessions_Async::DescribePlayerSessions(const FString& GameSessionId,
	const FString& PlayerId, const FString& PlayerSessionId, const FString& PlayerSessionStatusFilter, int32 Limit,
	const FString& NextToken)
{
	UDescribePlayerSessions_Async* Proxy = NewObject<UDescribePlayerSessions_Async>();
	Proxy->Var_GameSessionId = GameSessionId;
	Proxy->Var_PlayerId = PlayerId;
	Proxy->Var_PlayerSessionId = PlayerSessionId;
	Proxy->Var_PlayerSessionStatusFilter = PlayerSessionStatusFilter;
	Proxy->Var_Limit = Limit;
	Proxy->Var_NextToken = NextToken;
	return Proxy;
}

void UDescribePlayerSessions_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::DescribePlayerSessionsRequest Request;
	if(!Var_GameSessionId.IsEmpty())
	{
		Request.SetGameSessionId(TCHAR_TO_UTF8(*Var_GameSessionId));
	}
	if(!Var_PlayerId.IsEmpty())
	{
		Request.SetPlayerId(TCHAR_TO_UTF8(*Var_PlayerId));
	}
	if(!Var_PlayerSessionId.IsEmpty())
	{
		Request.SetPlayerSessionId(TCHAR_TO_UTF8(*Var_PlayerSessionId));
	}
	if(!Var_PlayerSessionStatusFilter.IsEmpty())
	{
		Request.SetPlayerSessionStatusFilter(TCHAR_TO_UTF8(*Var_PlayerSessionStatusFilter));
	}
	Request.SetLimit(Var_Limit);
	if(!Var_NextToken.IsEmpty())
	{
		Request.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
	}

	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribePlayerSessionsRequest&, const Aws::GameLift::Model::DescribePlayerSessionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				TArray<FPlayerSession> PlayerSessions;
				for (auto PlayerSession : outcome.GetResult().GetPlayerSessions())
				{
					PlayerSessions.Add(PlayerSession);
				}
				Success.Broadcast(PlayerSessions, FString(outcome.GetResult().GetNextToken().c_str()), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(TArray<FPlayerSession>(), FString(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->DescribePlayerSessionsAsync(Request, AsyncCallback);
}

void UDescribePlayerSessions_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(TArray<FPlayerSession>(), FString(), Error);
}
