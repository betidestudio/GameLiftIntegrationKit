//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "DeleteMatchmakingRuleSet_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeleteMatchmakingRuleSetAsync, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UDeleteMatchmakingRuleSet_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", DisplayName = "Delete Matchmaking RuleSet"), Category = "AWS Integration Kit|GameLift")
	static UDeleteMatchmakingRuleSet_Async* DeleteMatchmakingRuleSet(FString Name);

	UPROPERTY(BlueprintAssignable)
	FOnDeleteMatchmakingRuleSetAsync Success;

	UPROPERTY(BlueprintAssignable)
	FOnDeleteMatchmakingRuleSetAsync Failure;

	FString Var_Name;

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;
};
