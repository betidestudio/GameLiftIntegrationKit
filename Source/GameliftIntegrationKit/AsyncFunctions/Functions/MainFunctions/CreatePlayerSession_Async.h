// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AsyncFunctions/GameliftBaseFunction.h"
#include "CreatePlayerSession_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreatePlayerSessionAsyncOutputPin, const FPlayerSession&, PlayerSession,FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UCreatePlayerSession_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Create Player Session"), Category = "AWS Integration Kit|GameLift")
	static UCreatePlayerSession_Async* CreatePlayerSession(FString GameSessionId, FString PlayerId, FString PlayerData);

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	FString Var_GameSessionId;
	FString Var_PlayerId;
	FString Var_PlayerData;

	UPROPERTY(BlueprintAssignable)
	FCreatePlayerSessionAsyncOutputPin Success;

	UPROPERTY(BlueprintAssignable)
	FCreatePlayerSessionAsyncOutputPin Failure;
	
};
