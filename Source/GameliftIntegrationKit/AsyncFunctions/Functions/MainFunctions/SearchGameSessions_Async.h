//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AsyncFunctions/GameliftBaseFunction.h"
#include "SearchGameSessions_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSearchGameSessionsAsyncOutputPin, const TArray<FGLGameSession>&, GameSession,FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API USearchGameSessions_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Search Game Sessions"), Category = "AWS Integration Kit|GameLift")
	static USearchGameSessions_Async* SearchGameSessions(FString AliasId, FString FilterExpression, FString SortExpression, FString FleetId, int32 Limit, FString Location, FString NextToken);

	virtual void ExecuteFailure(FGameLiftError Error) override;
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;

	FString Var_AliasId;
	FString Var_FilterExpression;
	FString Var_SortExpression;
	FString Var_FleetId;
	int32 Var_Limit;
	FString Var_Location;
	FString Var_NextToken;

	UPROPERTY(BlueprintAssignable)
	FSearchGameSessionsAsyncOutputPin Success;

	UPROPERTY(BlueprintAssignable)
	FSearchGameSessionsAsyncOutputPin Failure;
};
