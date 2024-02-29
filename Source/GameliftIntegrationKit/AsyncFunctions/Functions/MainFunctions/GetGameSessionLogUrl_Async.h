// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "GetGameSessionLogUrl_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGetGameSessionLogUrlSuccess, FString, PreSignedUrl, FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UGetGameSessionLogUrl_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", DisplayName = "Get Game Session Log Url"), Category = "AWS Integration Kit|GameLift")
	static UGetGameSessionLogUrl_Async* GetGameSessionLogUrl(FString GameSessionId);

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;
	
	FString Var_GameSessionId;
	
	UPROPERTY(BlueprintAssignable)
		FOnGetGameSessionLogUrlSuccess Success;
	UPROPERTY(BlueprintAssignable)
		FOnGetGameSessionLogUrlSuccess Failure;
	
};
