// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "DescribeGameSessionPlacement_Async.h"

#include "Async/Async.h"
#include "aws/gamelift/model/DescribeGameSessionPlacementRequest.h"

UDescribeGameSessionPlacement_Async* UDescribeGameSessionPlacement_Async::DescribeGameSessionPlacement(
	FString PlacementId)
{
	UDescribeGameSessionPlacement_Async* Obj = NewObject<UDescribeGameSessionPlacement_Async>();
	Obj->Var_PlacementId = PlacementId;
	return Obj;
}

void UDescribeGameSessionPlacement_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::DescribeGameSessionPlacementRequest GameLiftRequest;
	if(!Var_PlacementId.IsEmpty())
	{
		GameLiftRequest.SetPlacementId(TCHAR_TO_UTF8(*Var_PlacementId));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::DescribeGameSessionPlacementRequest&, const Aws::GameLift::Model::DescribeGameSessionPlacementOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				Success.Broadcast(outcome.GetResult().GetGameSessionPlacement(), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(FGameSessionPlacement(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->DescribeGameSessionPlacementAsync(GameLiftRequest, AsyncCallback);
}

void UDescribeGameSessionPlacement_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FGameSessionPlacement(), Error);
}
