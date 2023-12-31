//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "DescribeMatchmaking_Async.h"

#include "Async.h"
#include "aws/gamelift/model/DescribeMatchmakingRequest.h"

UDescribeMatchmaking_Async* UDescribeMatchmaking_Async::DescribeMatchmaking(TArray<FString> TicketIds)
{
	UDescribeMatchmaking_Async* Obj = NewObject<UDescribeMatchmaking_Async>();
	Obj->Var_TicketIds = TicketIds;
	return Obj;
}

void UDescribeMatchmaking_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(TArray<FMatchmakingTicket>(), Error);
}

void UDescribeMatchmaking_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::DescribeMatchmakingRequest GameLiftRequest;
	for (FString TicketId : Var_TicketIds)
	{
		GameLiftRequest.AddTicketIds(TCHAR_TO_UTF8(*TicketId));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeMatchmakingRequest&, const Aws::GameLift::Model::DescribeMatchmakingOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				TArray<FMatchmakingTicket> Tickets;
				for (auto Ticket : outcome.GetResult().GetTicketList())
				{
					Tickets.Add(FMatchmakingTicket(Ticket));
				}
				Success.Broadcast(Tickets, FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(TArray<FMatchmakingTicket>(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->DescribeMatchmakingAsync(GameLiftRequest, AsyncCallback);
}
