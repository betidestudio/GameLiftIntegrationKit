//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "StartMatchmaking_Async.h"

#include "aws/gamelift/model/StartMatchmakingRequest.h"
#include "aws/iam/IAMClient.h"
#include "aws/s3/S3Client.h"

UStartMatchmaking_Async* UStartMatchmaking_Async::StartMatchmaking(FStartMatchmakingRequest Request)
{
	UStartMatchmaking_Async* object = NewObject<UStartMatchmaking_Async>();
	object->Var_Request = Request;
	return object;
}

void UStartMatchmaking_Async::Activate()
{
	Super::Activate();
}

void UStartMatchmaking_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FMatchmakingTicket(), Error);
}

void UStartMatchmaking_Async::StartMatchmaking_Async()
{
	UE_LOG(LogTemp, Warning, TEXT("StartMatchmaking_Async: StartMatchmaking_Async"));
}

void UStartMatchmaking_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	UE_LOG(LogTemp, Warning, TEXT("StartMatchmaking_Async: ContinueProcess"));
	Aws::GameLift::Model::StartMatchmakingRequest GameliftRequest;
	if(!Var_Request.ConfigurationName.IsEmpty())
	{
		GameliftRequest.SetConfigurationName(TCHAR_TO_UTF8(*Var_Request.ConfigurationName));
		//GameliftRequest.SetConfigurationName("arn:aws:gamelift:us-west-2:814880110677:matchmakingconfiguration/ConfigMMR1");
	}
	Aws::GameLift::Model::Player player;
	player.SetPlayerId("185147d7-fd2a-558c-36a6-804bce0ea62e");
	player.SetTeam("red");
	GameliftRequest.AddPlayers(player);
	if(!Var_Request.TicketId.IsEmpty())
	{
		GameliftRequest.SetTicketId(TCHAR_TO_UTF8(*Var_Request.TicketId));
	}
	UE_LOG(LogTemp, Warning, TEXT("StartMatchmaking_Async: ContinueProcess 2"));
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*,
	                            const Aws::GameLift::Model::StartMatchmakingRequest&,
	                            const Aws::GameLift::Model::StartMatchmakingOutcome& outcome,
	                            const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context)
	{
		UE_LOG(LogTemp, Warning, TEXT("StartMatchmaking_Async: ContinueProcess 4"));
		SetReadyToDestroy();
		MarkAsGarbage();
		/*
		AsyncTask(ENamedThreads::GameThread, [outcome,this]
		{
			//SetReadyToDestroy();
			//MarkAsGarbage();
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
		*/
	};
	
	
	UE_LOG(LogTemp, Warning, TEXT("StartMatchmaking_Async: ContinueProcess 3"));
	AWSObject->Var_GameLiftClient->StartMatchmakingAsync(GameliftRequest, AsyncCallback);
}
