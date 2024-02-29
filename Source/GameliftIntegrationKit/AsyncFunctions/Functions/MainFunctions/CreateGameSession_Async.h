//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "CreateGameSession_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateGameSessionAsyncOutputPin, const FGLGameSession&, GameSession,FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UCreateGameSession_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Create Game Session"), Category = "AWS Integration Kit|GameLift")
	static UCreateGameSession_Async* CreateGameSession(FString AliasId, FString CreatorId, FString FleetId, TArray<FGameProperty> GameProperties, FString GameSessionData, FString GameSessionId, FString IdempotencyToken, FString Name, int32 MaximumPlayerSessionCount, FString Location);
	

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	FString Var_AliasId;
	FString Var_CreatorId;
	FString Var_FleetId;
	TArray<FGameProperty> Var_GameProperties;
	FString Var_GameSessionData;
	FString Var_GameSessionId;
	FString Var_IdempotencyToken;
	FString Var_Name;
	int32 Var_MaximumPlayerSessionCount;
	FString Var_Location;

	UPROPERTY(BlueprintAssignable)
	FCreateGameSessionAsyncOutputPin Success;

	UPROPERTY(BlueprintAssignable)
	FCreateGameSessionAsyncOutputPin Failure;

	
};
