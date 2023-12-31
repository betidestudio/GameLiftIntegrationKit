//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "StartMatchmaking_Async.h"

#include "aws/gamelift/model/StartMatchmakingRequest.h"

UStartMatchmaking_Async* UStartMatchmaking_Async::StartMatchmaking(FStartMatchmakingRequest Request)
{
	UStartMatchmaking_Async* object = NewObject<UStartMatchmaking_Async>();
	object->Var_Request = Request;
	return object;
}

void UStartMatchmaking_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FMatchmakingTicket(), Error);
}

void UStartMatchmaking_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::StartMatchmakingRequest GameliftRequest;
	GameliftRequest.SetConfigurationName(TCHAR_TO_UTF8(*Var_Request.ConfigurationName));
	for (FGameliftPlayer Player : Var_Request.Players)
	{
		GameliftRequest.AddPlayers(Player.ToGameliftPlayer());
	}
	GameliftRequest.SetTicketId(TCHAR_TO_UTF8(*Var_Request.TicketId));
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::StartMatchmakingRequest&, const Aws::GameLift::Model::StartMatchmakingOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
	
	AWSObject->Var_GameLiftClient->StartMatchmakingAsync(GameliftRequest, AsyncCallback);
}
