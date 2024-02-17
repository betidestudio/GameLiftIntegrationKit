//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "DeleteMatchmakingConfiguration_Async.h"

#include "aws/gamelift/model/DeleteMatchmakingConfigurationRequest.h"

UDeleteMatchmakingConfiguration_Async* UDeleteMatchmakingConfiguration_Async::
DeleteMatchmakingConfiguration(FString Name)
{
	UDeleteMatchmakingConfiguration_Async* Obj = NewObject<UDeleteMatchmakingConfiguration_Async>();
	Obj->Var_Name = Name;
	return Obj;
}

void UDeleteMatchmakingConfiguration_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::DeleteMatchmakingConfigurationRequest GameLiftRequest;
	if(!Var_Name.IsEmpty())
	{
		GameLiftRequest.SetName(TCHAR_TO_UTF8(*Var_Name));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient* Client, const Aws::GameLift::Model::DeleteMatchmakingConfigurationRequest& Request, const Aws::GameLift::Model::DeleteMatchmakingConfigurationOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext> Context)
	{
		AsyncTask(ENamedThreads::GameThread, [Outcome, this]()
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
	AWSObject->Var_GameLiftClient->DeleteMatchmakingConfigurationAsync(GameLiftRequest, AsyncCallback);
}

void UDeleteMatchmakingConfiguration_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(Error);
}
