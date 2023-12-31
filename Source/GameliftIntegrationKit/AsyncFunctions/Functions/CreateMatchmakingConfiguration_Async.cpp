﻿//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "CreateMatchmakingConfiguration_Async.h"

#include "Async.h"
#include "aws/gamelift/model/CreateMatchmakingConfigurationRequest.h"

UCreateMatchmakingConfiguration_Async* UCreateMatchmakingConfiguration_Async::CreateMatchmakingConfiguration(
	FCreateMatchmakingConfigurationRequest Request)
{
	UCreateMatchmakingConfiguration_Async* Obj = NewObject<UCreateMatchmakingConfiguration_Async>();
	Obj->Var_Request = Request;
	return Obj;
}

void UCreateMatchmakingConfiguration_Async::ContinueProcess(UGameliftObject* AWSObject)
{
	Aws::GameLift::Model::CreateMatchmakingConfigurationRequest GameLiftRequest;
	GameLiftRequest.SetAcceptanceRequired(Var_Request.bAcceptanceRequired);
	GameLiftRequest.SetName(TCHAR_TO_UTF8(*Var_Request.Name));
	GameLiftRequest.SetRequestTimeoutSeconds(Var_Request.RequestTimeoutSeconds);
	GameLiftRequest.SetRuleSetName(TCHAR_TO_UTF8(*Var_Request.RuleSetName));
	GameLiftRequest.SetAcceptanceTimeoutSeconds(Var_Request.AcceptanceTimeoutSeconds);
	GameLiftRequest.SetAdditionalPlayerCount(Var_Request.AdditionalPlayerCount);
	GameLiftRequest.SetBackfillMode(static_cast<Aws::GameLift::Model::BackfillMode>(Var_Request.BackfillMode.GetValue()));
	GameLiftRequest.SetCustomEventData(TCHAR_TO_UTF8(*Var_Request.CustomEventData));
	GameLiftRequest.SetDescription(TCHAR_TO_UTF8(*Var_Request.Description));
	GameLiftRequest.SetFlexMatchMode(static_cast<Aws::GameLift::Model::FlexMatchMode>(Var_Request.FlexMatchMode.GetValue()));
	Aws::Vector<Aws::GameLift::Model::GameProperty> GameProperties;
	for(int32 i = 0; i < Var_Request.GameProperties.Num(); i++)
	{
		GameProperties.push_back(Var_Request.GameProperties[i].ToGameProperty());
	}
	GameLiftRequest.SetGameProperties(GameProperties);
	Aws::Vector<Aws::String> GameSessionQueueArns;
	for(int32 i = 0; i < Var_Request.GameSessionQueueArns.Num(); i++)
	{
		GameSessionQueueArns.push_back(TCHAR_TO_UTF8(*Var_Request.GameSessionQueueArns[i]));
	}
	GameLiftRequest.SetGameSessionQueueArns(GameSessionQueueArns);
	GameLiftRequest.SetGameSessionData(TCHAR_TO_UTF8(*Var_Request.GameSessionData));
	GameLiftRequest.SetNotificationTarget(TCHAR_TO_UTF8(*Var_Request.NotificationTarget));
	auto AsyncCallback = [this](const Aws::GameLift::GameLiftClient*, const Aws::GameLift::Model::CreateMatchmakingConfigurationRequest&, const Aws::GameLift::Model::CreateMatchmakingConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				Success.Broadcast(FMatchmakingConfiguration(outcome.GetResult().GetConfiguration()), FGameLiftError());
			}
			else
			{
				FGameLiftError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.ErrorType = static_cast<EGameLiftErrors>(outcome.GetError().GetErrorType());
				Error.GetMessageA = FString(outcome.GetError().GetMessageA().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessageW().c_str());
				Failure.Broadcast(FMatchmakingConfiguration(), Error);
			}
		}
		);
	};
	AWSObject->Var_GameLiftClient->CreateMatchmakingConfigurationAsync(GameLiftRequest, AsyncCallback);
}

void UCreateMatchmakingConfiguration_Async::ExecuteFailure(FGameLiftError Error)
{
	Failure.Broadcast(FMatchmakingConfiguration(), Error);
}
