// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "DescribeGameSessions_Async.h"

#include "Async/Async.h"
#include "aws/gamelift/model/DescribeGameSessionsRequest.h"

UDescribeGameSessions_Async* UDescribeGameSessions_Async::DescribeGameSessions(FString AliasId, FString FleetId,
	FString GameSessionId, FString GameSessionStatusFilter, FString Location, int32 Limit, FString NextToken)
{
	UDescribeGameSessions_Async* Obj = NewObject<UDescribeGameSessions_Async>();
	Obj->Var_AliasId = AliasId;
	Obj->Var_FleetId = FleetId;
	Obj->Var_GameSessionId = GameSessionId;
	Obj->Var_GameSessionStatusFilter = GameSessionStatusFilter;
	Obj->Var_Location = Location;
	Obj->Var_Limit = Limit;
	Obj->Var_NextToken = NextToken;
	return Obj;
}

void UDescribeGameSessions_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::DescribeGameSessionsRequest GameLiftRequest;
	if(!Var_AliasId.IsEmpty())
	{
		GameLiftRequest.SetAliasId(TCHAR_TO_UTF8(*Var_AliasId));
	}
	if(!Var_FleetId.IsEmpty())
	{
		GameLiftRequest.SetFleetId(TCHAR_TO_UTF8(*Var_FleetId));
	}
	if(!Var_GameSessionId.IsEmpty())
	{
		GameLiftRequest.SetGameSessionId(TCHAR_TO_UTF8(*Var_GameSessionId));
	}
	GameLiftRequest.SetLimit(Var_Limit);
	if(!Var_NextToken.IsEmpty())
	{
		GameLiftRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
	}
	if(!Var_Location.IsEmpty())
	{
		GameLiftRequest.SetLocation(TCHAR_TO_UTF8(*Var_Location));
	}
	if(!Var_GameSessionStatusFilter.IsEmpty())
	{
		GameLiftRequest.SetStatusFilter(TCHAR_TO_UTF8(*Var_GameSessionStatusFilter));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameSessionsRequest&, const Aws::GameLift::Model::DescribeGameSessionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				TArray<FGLGameSession> GameSessions;
				for (auto GameSession : outcome.GetResult().GetGameSessions())
				{
					GameSessions.Add(FGLGameSession(GameSession));
				}
				Success.Broadcast(GameSessions, FString(outcome.GetResult().GetNextToken().c_str()), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(TArray<FGLGameSession>(), FString(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->DescribeGameSessionsAsync(GameLiftRequest, AsyncCallback);
}

void UDescribeGameSessions_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(TArray<FGLGameSession>(), FString(), Error);
}
