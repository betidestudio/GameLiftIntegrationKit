// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "DescribePlayerSessions_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDescribePlayerSessionsSuccess, const TArray<FPlayerSession>&, PlayerSessions, const FString&, NextToken, FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UDescribePlayerSessions_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Describe Player Sessions"), Category = "AWS Integration Kit|GameLift")
		static UDescribePlayerSessions_Async* DescribePlayerSessions(const FString& GameSessionId, const FString& PlayerId, const FString& PlayerSessionId, const FString& PlayerSessionStatusFilter, int32 Limit, const FString& NextToken);

	
	FString Var_GameSessionId;
	FString Var_PlayerId;
	FString Var_PlayerSessionId;
	FString Var_PlayerSessionStatusFilter;
	int32 Var_Limit;
	FString Var_NextToken;

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	UPROPERTY(BlueprintAssignable)
		FOnDescribePlayerSessionsSuccess Success;

	UPROPERTY(BlueprintAssignable)
		FOnDescribePlayerSessionsSuccess Failure;
};
