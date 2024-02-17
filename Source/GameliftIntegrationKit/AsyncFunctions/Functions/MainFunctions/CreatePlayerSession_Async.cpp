// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatePlayerSession_Async.h"

#include "Async.h"
#include "aws/gamelift/model/CreatePlayerSessionRequest.h"

UCreatePlayerSession_Async* UCreatePlayerSession_Async::CreatePlayerSession(FString GameSessionId, FString PlayerId,
	FString PlayerData)
{
	UCreatePlayerSession_Async* object = NewObject<UCreatePlayerSession_Async>();
	object->Var_GameSessionId = GameSessionId;
	object->Var_PlayerId = PlayerId;
	object->Var_PlayerData = PlayerData;
	return object;
}

void UCreatePlayerSession_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::CreatePlayerSessionRequest GameliftRequest;
	if(!Var_GameSessionId.IsEmpty())
	{
		GameliftRequest.SetGameSessionId(TCHAR_TO_UTF8(*Var_GameSessionId));
	}
	if(!Var_PlayerId.IsEmpty())
	{
		GameliftRequest.SetPlayerId(TCHAR_TO_UTF8(*Var_PlayerId));
	}
	if(!Var_PlayerData.IsEmpty())
	{
		GameliftRequest.SetPlayerData(TCHAR_TO_UTF8(*Var_PlayerData));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreatePlayerSessionRequest&, const Aws::GameLift::Model::CreatePlayerSessionOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				Success.Broadcast(outcome.GetResult().GetPlayerSession(), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(FPlayerSession(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->CreatePlayerSessionAsync(GameliftRequest, AsyncCallback);
}

void UCreatePlayerSession_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FPlayerSession(), Error);
}
