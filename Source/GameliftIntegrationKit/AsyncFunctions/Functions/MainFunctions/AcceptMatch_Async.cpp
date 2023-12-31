//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "AcceptMatch_Async.h"

#include "Async.h"
#include "aws/gamelift/model/AcceptMatchRequest.h"

UAcceptMatch_Async* UAcceptMatch_Async::AcceptMatch(FAcceptMatchRequest Request)
{
	UAcceptMatch_Async* Obj = NewObject<UAcceptMatch_Async>();
	Obj->Var_Request = Request;
	return Obj;
}

void UAcceptMatch_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(Error);
}

void UAcceptMatch_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::AcceptMatchRequest GameLiftRequest;
	GameLiftRequest.SetTicketId(TCHAR_TO_UTF8(*Var_Request.TicketId));
	for (FString PlayerId : Var_Request.PlayerId)
	{
		GameLiftRequest.AddPlayerIds(TCHAR_TO_UTF8(*PlayerId));
	}
	GameLiftRequest.SetAcceptanceType(static_cast<Aws::GameLift::Model::AcceptanceType>(Var_Request.AcceptanceType.GetValue()));
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::AcceptMatchRequest&, const Aws::GameLift::Model::AcceptMatchOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
	AWSObject->Var_GameLiftClient->AcceptMatchAsync(GameLiftRequest, AsyncCallback);
}
