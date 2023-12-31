// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AsyncFunctions/GameliftBaseFunction.h"
#include "StartGameSessionPlacement_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStartGameSessionPlacementOutput, const FGameSessionPlacement&, GameSessionPlacement, FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UStartGameSessionPlacement_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Start Game Session Placement"), Category = "AWS Integration Kit|GameLift")
	static UStartGameSessionPlacement_Async* StartGameSessionPlacement(TArray<FDesiredPlayerSession> DesiredPlayerSessions, TArray<FGameProperty> GameProperties, FString GameSessionData, FString GameSessionName, FString GameSessionQueueName, int32 MaxPlayerSessionCount, FString PlacementId, TArray<FPlayerLatency> PlayerLatencies);


	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	TArray<FDesiredPlayerSession> Var_DesiredPlayerSessions;
	TArray<FGameProperty> Var_GameProperties;
	FString Var_GameSessionData;
	FString Var_GameSessionName;
	FString Var_GameSessionQueueName;
	int32 Var_MaxPlayerSessionCount;
	FString Var_PlacementId;
	TArray<FPlayerLatency> Var_PlayerLatencies;

	UPROPERTY(BlueprintAssignable)
	FOnStartGameSessionPlacementOutput Success;

	UPROPERTY(BlueprintAssignable)
	FOnStartGameSessionPlacementOutput Failure;
};
