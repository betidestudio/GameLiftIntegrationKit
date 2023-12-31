// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "DescribeGameSessionDetails_Async.h"

#include "Async.h"
#include "aws/gamelift/model/DescribeGameSessionDetailsRequest.h"

UDescribeGameSessionDetails_Async* UDescribeGameSessionDetails_Async::DescribeGameSessionDetails(FString AliasID,
	FString FleetID, FString GameSessionID, FString StatusFilter, FString Location, int32 Limit, FString NextToken)
{
	UDescribeGameSessionDetails_Async* Obj = NewObject<UDescribeGameSessionDetails_Async>();
	Obj->Var_AliasID = AliasID;
	Obj->Var_FleetID = FleetID;
	Obj->Var_GameSessionID = GameSessionID;
	Obj->Var_Limit = Limit;
	Obj->Var_NextToken = NextToken;
	Obj->Var_StatusFilter = StatusFilter;
	Obj->Var_Location = Location;
	return Obj;
}

void UDescribeGameSessionDetails_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::DescribeGameSessionDetailsRequest Request;
	Request.SetAliasId(TCHAR_TO_UTF8(*Var_AliasID));
	Request.SetFleetId(TCHAR_TO_UTF8(*Var_FleetID));
	Request.SetGameSessionId(TCHAR_TO_UTF8(*Var_GameSessionID));
	Request.SetLimit(Var_Limit);
	Request.SetNextToken(TCHAR_TO_UTF8(*Var_NextToken));
	Request.SetStatusFilter(TCHAR_TO_UTF8(*Var_StatusFilter));

	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameSessionDetailsRequest&, const Aws::GameLift::Model::DescribeGameSessionDetailsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				TArray<FGameSessionDetail> GameSessionDetails;
				for (auto GameSessionDetail : outcome.GetResult().GetGameSessionDetails())
				{
					GameSessionDetails.Add(FGameSessionDetail(GameSessionDetail));
				}
				Success.Broadcast(GameSessionDetails, FString(outcome.GetResult().GetNextToken().c_str()), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(TArray<FGameSessionDetail>(), FString(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->DescribeGameSessionDetailsAsync(Request, AsyncCallback);
}

void UDescribeGameSessionDetails_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(TArray<FGameSessionDetail>(), FString(), Error);
}
