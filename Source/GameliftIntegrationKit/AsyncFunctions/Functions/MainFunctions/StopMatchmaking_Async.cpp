//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "StopMatchmaking_Async.h"

#include "Async/Async.h"
#include "aws/gamelift/model/StopMatchmakingRequest.h"

UStopMatchmaking_Async* UStopMatchmaking_Async::StopMatchmaking(FString TicketId)
{
	UStopMatchmaking_Async* Obj = NewObject<UStopMatchmaking_Async>();
	Obj->Var_TicketId = TicketId;
	return Obj;
}

void UStopMatchmaking_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(Error);
}

void UStopMatchmaking_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::StopMatchmakingRequest GameLiftRequest;
	if(!Var_TicketId.IsEmpty())
	{
		GameLiftRequest.SetTicketId(TCHAR_TO_UTF8(*Var_TicketId));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StopMatchmakingRequest&, const Aws::GameLift::Model::StopMatchmakingOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				Success.Broadcast(FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->StopMatchmakingAsync(GameLiftRequest, AsyncCallback);
}
