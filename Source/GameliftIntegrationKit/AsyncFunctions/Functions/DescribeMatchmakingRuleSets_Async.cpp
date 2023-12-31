//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "DescribeMatchmakingRuleSets_Async.h"

#include "aws/gamelift/model/DescribeMatchmakingRuleSetsRequest.h"

UDescribeMatchmakingRuleSets_Async* UDescribeMatchmakingRuleSets_Async::DescribeMatchmakingRuleSets(
	FDescribeMatchmakingRuleSetsRequest Request)
{
	UDescribeMatchmakingRuleSets_Async* Obj = NewObject<UDescribeMatchmakingRuleSets_Async>();
	Obj->Var_Request = Request;
	return Obj;
}

void UDescribeMatchmakingRuleSets_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::DescribeMatchmakingRuleSetsRequest GameLiftRequest;
	GameLiftRequest.SetLimit(Var_Request.Limit);
	GameLiftRequest.SetNextToken(TCHAR_TO_UTF8(*Var_Request.NextToken));
	for (FString Name : Var_Request.Names)
	{
		GameLiftRequest.AddNames(TCHAR_TO_UTF8(*Name));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::DescribeMatchmakingRuleSetsRequest& Request, const Aws::GameLift::Model::DescribeMatchmakingRuleSetsOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext> Context)
	{
		AsyncTask(ENamedThreads::GameThread, [Outcome, this]()
		{
			if (Outcome.IsSuccess())
			{
				TArray<FMatchmakingRuleSet> RuleSets;
				for (auto RuleSet : Outcome.GetResult().GetRuleSets())
				{
					RuleSets.Add(FMatchmakingRuleSet(RuleSet));
				}
				Success.Broadcast(RuleSets, FString(Outcome.GetResult().GetNextToken().c_str()), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(Outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(Outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(Outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(Outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(TArray<FMatchmakingRuleSet>(), FString(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->DescribeMatchmakingRuleSetsAsync(GameLiftRequest, AsyncCallback);
}

void UDescribeMatchmakingRuleSets_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(TArray<FMatchmakingRuleSet>(), FString(), Error);
}
