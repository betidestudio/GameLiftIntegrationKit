﻿//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "SearchGameSessions_Async.h"

#include "Async.h"
#include "aws/gamelift/model/SearchGameSessionsRequest.h"

USearchGameSessions_Async* USearchGameSessions_Async::SearchGameSessions(FString AliasId, FString FilterExpression,
	FString SortExpression, FString FleetId, int32 Limit, FString Location, FString NextToken)
{
	USearchGameSessions_Async* Obj = NewObject<USearchGameSessions_Async>();
	Obj->Var_AliasId = AliasId;
	Obj->Var_FilterExpression = FilterExpression;
	Obj->Var_SortExpression = SortExpression;
	Obj->Var_FleetId = FleetId;
	Obj->Var_Limit = Limit;
	Obj->Var_Location = Location;
	Obj->Var_NextToken = NextToken;
	return Obj;
}

void USearchGameSessions_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(TArray<FGLGameSession>(), Error);
}

void USearchGameSessions_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::SearchGameSessionsRequest GameLiftRequest;
	GameLiftRequest.SetAliasId(TCHAR_TO_UTF8(*Var_AliasId));
	GameLiftRequest.SetFilterExpression(TCHAR_TO_UTF8(*Var_FilterExpression));
	GameLiftRequest.SetSortExpression(TCHAR_TO_UTF8(*Var_SortExpression));
	GameLiftRequest.SetFleetId(TCHAR_TO_UTF8(*Var_FleetId));
	GameLiftRequest.SetLimit(Var_Limit);
	GameLiftRequest.SetLocation(TCHAR_TO_UTF8(*Var_Location));
	GameLiftRequest.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::SearchGameSessionsRequest&, const Aws::GameLift::Model::SearchGameSessionsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				TArray<FGLGameSession> GameSessions;
				for(auto GameSession : outcome.GetResult().GetGameSessions())
				{
					GameSessions.Add(FGLGameSession(GameSession));
				}
				Success.Broadcast(GameSessions, FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(TArray<FGLGameSession>(), Error);
			}
		});
	};
	
}