//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "CreateMatchmakingRuleSet_Async.h"

#include "aws/gamelift/model/CreateMatchmakingRuleSetRequest.h"

UCreateMatchmakingRuleSet_Async* UCreateMatchmakingRuleSet_Async::CreateMatchmakingRuleSet(
	FCreateMatchmakingRuleSetRequest CreateMatchmakingRuleSetRequest)
{
	UCreateMatchmakingRuleSet_Async* Obj = NewObject<UCreateMatchmakingRuleSet_Async>();
	Obj->Var_Request = CreateMatchmakingRuleSetRequest;
	return Obj;
}

void UCreateMatchmakingRuleSet_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FMatchmakingRuleSet(), Error);
}

void UCreateMatchmakingRuleSet_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::CreateMatchmakingRuleSetRequest GameLiftRequest;
	GameLiftRequest.SetName(TCHAR_TO_UTF8(*Var_Request.Name));
	GameLiftRequest.SetRuleSetBody(TCHAR_TO_UTF8(*Var_Request.RuleSetBody));
	for(auto Property : Var_Request.Tags)
	{
		Aws::GameLift::Model::Tag Tag;
		Tag.SetKey(TCHAR_TO_UTF8(*Property.Key));
		Tag.SetValue(TCHAR_TO_UTF8(*Property.Value));
		GameLiftRequest.AddTags(Tag);
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::CreateMatchmakingRuleSetRequest& Request, const Aws::GameLift::Model::CreateMatchmakingRuleSetOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext> Context)
	{
		AsyncTask(ENamedThreads::GameThread, [Outcome, this]()
		{
			if(Outcome.IsSuccess())
			{
				Success.Broadcast(FMatchmakingRuleSet(Outcome.GetResult().GetRuleSet()), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(Outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(Outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(Outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(Outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(FMatchmakingRuleSet(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->CreateMatchmakingRuleSetAsync(GameLiftRequest, AsyncCallback);
}
