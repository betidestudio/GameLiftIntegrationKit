//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "ValidateMatchmakingRuleSet_Async.h"

#include "aws/gamelift/model/ValidateMatchmakingRuleSetRequest.h"

UValidateMatchmakingRuleSet_Async* UValidateMatchmakingRuleSet_Async::ValidateMatchmakingRuleSet(FString RuleSetBody)
{
	UValidateMatchmakingRuleSet_Async* Obj = NewObject<UValidateMatchmakingRuleSet_Async>();
	Obj->Var_RuleSetBody = RuleSetBody;
	return Obj;
}

void UValidateMatchmakingRuleSet_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::ValidateMatchmakingRuleSetRequest GameLiftRequest;
	GameLiftRequest.SetRuleSetBody(TCHAR_TO_UTF8(*Var_RuleSetBody));
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::ValidateMatchmakingRuleSetRequest&, const Aws::GameLift::Model::ValidateMatchmakingRuleSetOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				Success.Broadcast(outcome.GetResult().GetValid(), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(false, Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->ValidateMatchmakingRuleSetAsync(GameLiftRequest, AsyncCallback);
}

void UValidateMatchmakingRuleSet_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(false, Error);
}
