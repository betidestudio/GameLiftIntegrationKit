// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "CreatePlayerSessions_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreatePlayerSessionsOutput, const TArray<FPlayerSession>&, PlayerSessions, FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UCreatePlayerSessions_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Create Player Sessions"), Category = "AWS Integration Kit|GameLift")
	static UCreatePlayerSessions_Async* CreatePlayerSessions(FString GameSessionId, TArray<FString> PlayerIds, TMap<FString, FString> PlayerDataMap);

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	FString Var_GameSessionId;
	TArray<FString> Var_PlayerIds;
	TMap<FString, FString> Var_PlayerDataMap;

	UPROPERTY(BlueprintAssignable)
	FOnCreatePlayerSessionsOutput Success;

	UPROPERTY(BlueprintAssignable)
	FOnCreatePlayerSessionsOutput Failure;
};
