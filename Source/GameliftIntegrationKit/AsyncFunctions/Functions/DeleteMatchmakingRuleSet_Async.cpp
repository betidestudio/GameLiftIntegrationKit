//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "DeleteMatchmakingRuleSet_Async.h"

#include "aws/gamelift/model/DeleteMatchmakingRuleSetRequest.h"

UDeleteMatchmakingRuleSet_Async* UDeleteMatchmakingRuleSet_Async::DeleteMatchmakingRuleSet(FString Name)
{
	UDeleteMatchmakingRuleSet_Async* Obj = NewObject<UDeleteMatchmakingRuleSet_Async>();
	Obj->Var_Name = Name;
	return Obj;
}

void UDeleteMatchmakingRuleSet_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::DeleteMatchmakingRuleSetRequest GameLiftRequest;
	if(!Var_Name.IsEmpty())
	{
		GameLiftRequest.SetName(TCHAR_TO_UTF8(*Var_Name));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::DeleteMatchmakingRuleSetRequest& Request, const Aws::GameLift::Model::DeleteMatchmakingRuleSetOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext> Context)
	{
		AsyncTask(ENamedThreads::GameThread, [this, Outcome]()
		{
			if(Outcome.IsSuccess())
			{
				Success.Broadcast(FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(Outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(Outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(Outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(Outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->DeleteMatchmakingRuleSetAsync(GameLiftRequest, AsyncCallback);
}

void UDeleteMatchmakingRuleSet_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(Error);
}
