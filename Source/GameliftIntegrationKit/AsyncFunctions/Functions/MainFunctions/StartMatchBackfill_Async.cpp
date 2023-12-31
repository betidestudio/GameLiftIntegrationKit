//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "StartMatchBackfill_Async.h"

#include "Async.h"
#include "aws/gamelift/model/StartMatchBackfillRequest.h"
#include "aws/gamelift/model/StartMatchmakingRequest.h"

UStartMatchBackfill_Async* UStartMatchBackfill_Async::StartMatchBackfill(FStartMatchBackfillRequest Request)
{
	UStartMatchBackfill_Async* object = NewObject<UStartMatchBackfill_Async>();
	object->Var_Request = Request;
	return object;
}

void UStartMatchBackfill_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::StartMatchBackfillRequest GameliftRequest;
	GameliftRequest.SetConfigurationName(TCHAR_TO_UTF8(*Var_Request.ConfigurationName));
	for (FGameliftPlayer Player : Var_Request.Players)
	{
		GameliftRequest.AddPlayers(Player.ToGameliftPlayer());
	}
	GameliftRequest.SetTicketId(TCHAR_TO_UTF8(*Var_Request.TicketId));
	GameliftRequest.SetGameSessionArn(TCHAR_TO_UTF8(*Var_Request.GameSessionArn));
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StartMatchBackfillRequest&, const Aws::GameLift::Model::StartMatchBackfillOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				Success.Broadcast(FMatchmakingTicket(outcome.GetResult().GetMatchmakingTicket()), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(FMatchmakingTicket(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->StartMatchBackfillAsync(GameliftRequest, AsyncCallback);
	
}

void UStartMatchBackfill_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FMatchmakingTicket(), Error);
}
