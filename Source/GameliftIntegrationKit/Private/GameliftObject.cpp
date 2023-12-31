//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "GameliftObject.h"

#include "Async.h"
#include "UObjectIterator.h"
#include "aws/core/Aws.h"
#include "aws/core/auth/AWSCredentials.h"

void UGameliftObject::InitGameLift(UObject* WorldContextObject, FGameLiftSetup Settings, FOnGameliftSetupSuccess OnGameliftSetupSuccess)
{
	Aws::SDKOptions options;
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
	Aws::InitAPI(options);
	if(WorldContextObject)
	{
		UGameliftObject* AwsObject = nullptr;
		TArray<UGameliftObject*> Objects;
		for (TObjectIterator<UGameliftObject> Itr; Itr; ++Itr)
		{
			Objects.Add(*Itr);
		}
		if(Objects.Num()>0)
		{
			AwsObject = Objects[0];
		}
		else
		{
			AwsObject = NewObject<UGameliftObject>();
		}
		if(AwsObject)
		{
			AsyncTask(ENamedThreads::GameThread, [=]()
			{
				Aws::GameLift::GameLiftClientConfiguration* Var_ClientConfig = new Aws::GameLift::GameLiftClientConfiguration();
				Var_ClientConfig->region = TCHAR_TO_UTF8(*AwsObject->GameLiftSetup.Region);
				if(AwsObject->GameLiftSetup.OtherSettings.bOverrideDefaultClientConfig)
				{
					Var_ClientConfig->requestTimeoutMs = AwsObject->GameLiftSetup.OtherSettings.RequestTimeoutMs;
					Var_ClientConfig->connectTimeoutMs = AwsObject->GameLiftSetup.OtherSettings.ConnectTimeoutMs;
					Var_ClientConfig->userAgent = TCHAR_TO_UTF8(*AwsObject->GameLiftSetup.OtherSettings.UserAgent);
					Var_ClientConfig->scheme = static_cast<Aws::Http::Scheme>(AwsObject->GameLiftSetup.OtherSettings.Scheme.GetValue());
					Var_ClientConfig->useDualStack = AwsObject->GameLiftSetup.OtherSettings.bUseDualStack;
					Var_ClientConfig->useFIPS = AwsObject->GameLiftSetup.OtherSettings.bUseFIPS;
					Var_ClientConfig->verifySSL = AwsObject->GameLiftSetup.OtherSettings.bVerifyPeer;
				}
				Aws::Auth::AWSCredentials* Var_AWSCredentials = nullptr;
				if(AwsObject->GameLiftSetup.Credentials.AccessKeyId.Len()>0 && AwsObject->GameLiftSetup.Credentials.SecretAccessKey.Len()>0)
				{
					Var_AWSCredentials = new Aws::Auth::AWSCredentials(TCHAR_TO_UTF8(*AwsObject->GameLiftSetup.Credentials.AccessKeyId), TCHAR_TO_UTF8(*AwsObject->GameLiftSetup.Credentials.SecretAccessKey), TCHAR_TO_UTF8(*AwsObject->GameLiftSetup.Credentials.SessionToken));
				}
				if(Var_AWSCredentials)
				{
					AwsObject->Var_GameLiftClient = new Aws::GameLift::GameLiftClient(*Var_AWSCredentials,*Var_ClientConfig);
				}
				else
				{
					AwsObject->Var_GameLiftClient = new Aws::GameLift::GameLiftClient(*Var_ClientConfig);
				}
				OnGameliftSetupSuccess.ExecuteIfBound(true);
			});
		}
		else
		{
			OnGameliftSetupSuccess.ExecuteIfBound(false);
		}
	}
	else
	{
		OnGameliftSetupSuccess.ExecuteIfBound(false);
	}
}

bool UGameliftObject::ShutdownGameLift(UObject* WorldContextObject)
{
	Aws::SDKOptions options;
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
	Aws::ShutdownAPI(options);
	return true;
}
