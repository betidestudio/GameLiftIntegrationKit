// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "DescribeGameSessionDetails_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDescribeGameSessionDetailsSuccess, const TArray<FGameSessionDetail>&, GameSessionDetails, const FString&, NextToken, FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UDescribeGameSessionDetails_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Describe Game Session Details"), Category = "AWS Integration Kit|GameLift")
	static UDescribeGameSessionDetails_Async* DescribeGameSessionDetails(FString AliasID, FString FleetID, FString GameSessionID, FString StatusFilter, FString Location, int32 Limit, FString NextToken);
	
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	FString Var_AliasID;
	FString Var_FleetID;
	FString Var_GameSessionID;
	int32 Var_Limit;
	FString Var_NextToken;
	FString Var_StatusFilter;
	FString Var_Location;

	UPROPERTY(BlueprintAssignable)
		FOnDescribeGameSessionDetailsSuccess Success;
	UPROPERTY(BlueprintAssignable)
		FOnDescribeGameSessionDetailsSuccess Failure;
};
