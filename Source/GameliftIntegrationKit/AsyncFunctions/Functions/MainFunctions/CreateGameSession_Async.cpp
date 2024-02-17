//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "CreateGameSession_Async.h"

#include "Async.h"
#include "aws/gamelift/model/CreateGameSessionRequest.h"

UCreateGameSession_Async* UCreateGameSession_Async::CreateGameSession(FString AliasId, FString CreatorId,
	FString FleetId, TArray<FGameProperty> GameProperties, FString GameSessionData, FString GameSessionId,
	FString IdempotencyToken, FString Name, int32 MaximumPlayerSessionCount, FString Location)
{
	UCreateGameSession_Async* object = NewObject<UCreateGameSession_Async>();
	object->Var_AliasId = AliasId;
	object->Var_CreatorId = CreatorId;
	object->Var_FleetId = FleetId;
	object->Var_GameProperties = GameProperties;
	object->Var_GameSessionData = GameSessionData;
	object->Var_GameSessionId = GameSessionId;
	object->Var_IdempotencyToken = IdempotencyToken;
	object->Var_Name = Name;
	object->Var_MaximumPlayerSessionCount = MaximumPlayerSessionCount;
	object->Var_Location = Location;
	return object;
}

void UCreateGameSession_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::CreateGameSessionRequest GameliftRequest;
	if(!Var_AliasId.IsEmpty())
	{
		GameliftRequest.SetAliasId(TCHAR_TO_UTF8(*Var_AliasId));
	}
	if(!Var_CreatorId.IsEmpty())
	{
		GameliftRequest.SetCreatorId(TCHAR_TO_UTF8(*Var_CreatorId));
	}
	if(!Var_FleetId.IsEmpty())
	{
		GameliftRequest.SetFleetId(TCHAR_TO_UTF8(*Var_FleetId));
	}
	if (!Var_GameSessionData.IsEmpty())
	{
		GameliftRequest.SetGameSessionData(TCHAR_TO_UTF8(*Var_GameSessionData));
	}
	if (!Var_GameSessionId.IsEmpty())
	{
		GameliftRequest.SetGameSessionId(TCHAR_TO_UTF8(*Var_GameSessionId));
	}
	if(!Var_IdempotencyToken.IsEmpty())
	{
		GameliftRequest.SetIdempotencyToken(TCHAR_TO_UTF8(*Var_IdempotencyToken));
	}
	if(!Var_Name.IsEmpty())
	{
		GameliftRequest.SetName(TCHAR_TO_UTF8(*Var_Name));
	}
	if(Var_MaximumPlayerSessionCount > 0)
	{
		GameliftRequest.SetMaximumPlayerSessionCount(Var_MaximumPlayerSessionCount);
	}
	if(!Var_Location.IsEmpty())
	{
		GameliftRequest.SetLocation(TCHAR_TO_UTF8(*Var_Location));
	}
	if(Var_GameProperties.Num() > 0)
	{
		for (FGameProperty Property : Var_GameProperties)
		{
			GameliftRequest.AddGameProperties(Property.ToGameProperty());
		}
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateGameSessionRequest&, const Aws::GameLift::Model::CreateGameSessionOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				Success.Broadcast(outcome.GetResult().GetGameSession(), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(FGLGameSession(), Error);
			}
		});
	};
	AWSObject->Var_GameLiftClient->CreateGameSessionAsync(GameliftRequest, AsyncCallback);
}

void UCreateGameSession_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FGLGameSession(), Error);
}
