// Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "GetGameSessionLogUrl_Async.h"

#include "aws/gamelift/model/GetGameSessionLogUrlRequest.h"

UGetGameSessionLogUrl_Async* UGetGameSessionLogUrl_Async::GetGameSessionLogUrl(FString GameSessionId)
{
	UGetGameSessionLogUrl_Async* Obj = NewObject<UGetGameSessionLogUrl_Async>();
	Obj->Var_GameSessionId = GameSessionId;
	return Obj;
}

void UGetGameSessionLogUrl_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::GetGameSessionLogUrlRequest Request;
	if(!Var_GameSessionId.IsEmpty())
	{
		Request.SetGameSessionId(TCHAR_TO_UTF8(*Var_GameSessionId));
	}
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::GetGameSessionLogUrlRequest& Request, const Aws::GameLift::Model::GetGameSessionLogUrlOutcome& Outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>&) {
		if (Outcome.IsSuccess())
		{
			Success.Broadcast(Outcome.GetResult().GetPreSignedUrl().c_str(), FGameLiftError());
		}
		else
		{
			FGameLiftError Error;
			Error.ErrorMessage = FString(Outcome.GetError().GetMessage().c_str());
			Error.ExceptionName = FString(Outcome.GetError().GetExceptionName().c_str());
			Error.ErrorType = static_cast<EGameLiftErrors>(Outcome.GetError().GetErrorType());
			Error.GetMessageA = FString(Outcome.GetError().GetMessageA().c_str());
			Error.GetMessageW = FString(Outcome.GetError().GetMessageW().c_str());
			Failure.Broadcast("", Error);
		}
	};
	AWSObject->Var_GameLiftClient->GetGameSessionLogUrlAsync(Request, AsyncCallback);
}

void UGetGameSessionLogUrl_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast("", Error);
}
