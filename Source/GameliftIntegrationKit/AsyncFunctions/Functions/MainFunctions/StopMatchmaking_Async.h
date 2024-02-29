//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "StopMatchmaking_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStopMatchmakingAsyncOutputPin, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UStopMatchmaking_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Stop Matchmaking"), Category = "AWS Integration Kit|GameLift")
	static UStopMatchmaking_Async* StopMatchmaking(FString TicketId);

	UPROPERTY(BlueprintAssignable)
	FStopMatchmakingAsyncOutputPin Success;

	UPROPERTY(BlueprintAssignable)
	FStopMatchmakingAsyncOutputPin Failure;

	virtual void ExecuteFailure(FGameLiftError Error) override;
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	
	FString Var_TicketId;
};
