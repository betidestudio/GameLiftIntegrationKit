//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "DescribeMatchmakingConfigurations_Async.h"

#include "aws/gamelift/model/DescribeMatchmakingConfigurationsRequest.h"

UDescribeMatchmakingConfigurations_Async* UDescribeMatchmakingConfigurations_Async::DescribeMatchmakingConfigurations(
	FDescribeMatchmakingConfigurationsRequest Request)
{
	UDescribeMatchmakingConfigurations_Async* Obj = NewObject<UDescribeMatchmakingConfigurations_Async>();
	Obj->Var_Request = Request;
	return Obj;
}

void UDescribeMatchmakingConfigurations_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::DescribeMatchmakingConfigurationsRequest GameLiftRequest;
	Aws::Vector<Aws::String> Names;
	for(int32 i = 0; i < Var_Request.Names.Num(); i++)
	{
		Names.push_back(TCHAR_TO_UTF8(*Var_Request.Names[i]));
	}
	GameLiftRequest.SetNames(Names);
	GameLiftRequest.SetRuleSetName(TCHAR_TO_UTF8(*Var_Request.RuleSetName));
	GameLiftRequest.SetLimit(Var_Request.Limit);
	GameLiftRequest.SetNextToken(TCHAR_TO_UTF8(*Var_Request.NextToken));
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::DescribeMatchmakingConfigurationsRequest& Request, const Aws::GameLift::Model::DescribeMatchmakingConfigurationsOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext> Context)
	{
		AsyncTask(ENamedThreads::GameThread, [Outcome, this]()
		{
			if(Outcome.IsSuccess())
			{
				TArray<FMatchmakingConfiguration> MatchmakingConfigurations;
				for(int32 i = 0; i < Outcome.GetResult().GetConfigurations().size(); i++)
				{
					MatchmakingConfigurations.Add(FMatchmakingConfiguration(Outcome.GetResult().GetConfigurations()[i]));
				}
				Success.Broadcast(MatchmakingConfigurations, FString(Outcome.GetResult().GetNextToken().c_str()), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(Outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(Outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(Outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(Outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(TArray<FMatchmakingConfiguration>(), "", Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->DescribeMatchmakingConfigurationsAsync(GameLiftRequest, AsyncCallback);
}

void UDescribeMatchmakingConfigurations_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(TArray<FMatchmakingConfiguration>(), "", Error);
}
