//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "ValidateMatchmakingRuleSet_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnValidateMatchmakingRuleSetAsync, bool, Valid, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UValidateMatchmakingRuleSet_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Validate Matchmaking RuleSet"), Category = "AWS Integration Kit|GameLift")
	static UValidateMatchmakingRuleSet_Async* ValidateMatchmakingRuleSet(FString RuleSetBody);

	FString Var_RuleSetBody;

	UPROPERTY(BlueprintAssignable)
	FOnValidateMatchmakingRuleSetAsync Success;

	UPROPERTY(BlueprintAssignable)
	FOnValidateMatchmakingRuleSetAsync Failure;

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;
};
