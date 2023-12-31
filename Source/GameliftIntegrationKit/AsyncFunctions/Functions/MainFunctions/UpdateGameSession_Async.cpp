// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "UpdateGameSession_Async.h"

#include "Async.h"
#include "aws/gamelift/model/UpdateGameSessionRequest.h"

UUpdateGameSession_Async* UUpdateGameSession_Async::UpdateGameSession(const TArray<FGameProperty>& GameProperties,
	const FString& GameSessionId, int32 MaximumPlayerSessionCount, const FString& Name,
	EPlayerSessionCreationPolicy PlayerSessionCreationPolicy, EProtectionPolicy ProtectionPolicy)
{
	UUpdateGameSession_Async* Proxy = NewObject<UUpdateGameSession_Async>();
	Proxy->Var_GameProperties = GameProperties;
	Proxy->Var_GameSessionId = GameSessionId;
	Proxy->Var_MaximumPlayerSessionCount = MaximumPlayerSessionCount;
	Proxy->Var_Name = Name;
	Proxy->Var_PlayerSessionCreationPolicy = PlayerSessionCreationPolicy;
	Proxy->Var_ProtectionPolicy = ProtectionPolicy;
	return Proxy;
}

void UUpdateGameSession_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::UpdateGameSessionRequest Request;
	Request.SetGameSessionId(TCHAR_TO_UTF8(*Var_GameSessionId));
	Request.SetMaximumPlayerSessionCount(Var_MaximumPlayerSessionCount);
	Request.SetName(TCHAR_TO_UTF8(*Var_Name));
	Request.SetPlayerSessionCreationPolicy(static_cast<Aws::GameLift::Model::PlayerSessionCreationPolicy>(Var_PlayerSessionCreationPolicy.GetValue()));
	Request.SetProtectionPolicy(static_cast<Aws::GameLift::Model::ProtectionPolicy>(Var_ProtectionPolicy.GetValue()));
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::UpdateGameSessionRequest&, const Aws::GameLift::Model::UpdateGameSessionOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
	AWSObject->Var_GameLiftClient->UpdateGameSessionAsync(Request, AsyncCallback);
}

void UUpdateGameSession_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FGLGameSession(), Error);
}
