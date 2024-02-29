//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "DescribeMatchmaking_Async.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDescribeMatchmakingAsyncOutputPin, TArray<FMatchmakingTicket>, Result, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UDescribeMatchmaking_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Describe Matchmaking"), Category = "AWS Integration Kit|GameLift")
	static UDescribeMatchmaking_Async* DescribeMatchmaking(TArray<FString> TicketIds);

	TArray<FString> Var_TicketIds;

	UPROPERTY(BlueprintAssignable)
	FDescribeMatchmakingAsyncOutputPin Success;

	UPROPERTY(BlueprintAssignable)
	FDescribeMatchmakingAsyncOutputPin Failure;

	virtual void ExecuteFailure(FGameLiftError Error) override;
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
};
