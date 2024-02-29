// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "DescribeGameSessions_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDescribeGameSessionsOutput, const TArray<FGLGameSession>&, GameSessions, const FString&, NextToken, FGameLiftError, Error); 
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UDescribeGameSessions_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Describe Game Sessions"), Category = "AWS Integration Kit|GameLift")
	static UDescribeGameSessions_Async* DescribeGameSessions(FString AliasId, FString FleetId, FString GameSessionId, FString GameSessionStatusFilter, FString Location, int32 Limit, FString NextToken);

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	FString Var_AliasId;
	FString Var_FleetId;
	FString Var_GameSessionId;
	FString Var_GameSessionStatusFilter;
	FString Var_Location;
	int32 Var_Limit;
	FString Var_NextToken;

	UPROPERTY(BlueprintAssignable)
	FOnDescribeGameSessionsOutput Success;

	UPROPERTY(BlueprintAssignable)
	FOnDescribeGameSessionsOutput Failure;
};
