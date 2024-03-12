
//Copyright (c) 2024 Betide Studio. All Rights Reserved.


#include "GameliftBaseFunction.h"

void UGameliftBaseFunction::Activate()
{
	FGameLiftError Local_FailureResponse = FGameLiftError();
	Super::Activate();
	TArray<UGameliftObject*> Objects;
	for (TObjectIterator<UGameliftObject> Itr; Itr; ++Itr)
	{
		Objects.Add(*Itr);
	}
	if(Objects.Num()>0 && Objects[0])
	{
		if(!Objects[0]->Var_GameLiftClient)
		{
			Local_FailureResponse.ErrorMessage = "Cognito Client ID is empty";
			ExecuteFailure(Local_FailureResponse);
			SetReadyToDestroy();
		}
		else
		{
			ContinueProcess(Objects[0]);
		}
	}
	else
	{
		Local_FailureResponse.ErrorMessage = "No object found";
		ExecuteFailure(Local_FailureResponse);
		SetReadyToDestroy();
	}
}

void UGameliftBaseFunction::ContinueProcess(UGameliftObject* AWSObject)
{
}

void UGameliftBaseFunction::ExecuteFailure(FGameLiftError Error)
{
}
