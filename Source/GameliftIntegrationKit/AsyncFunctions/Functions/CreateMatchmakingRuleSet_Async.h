//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CreateMatchmakingRuleSet_Async.generated.h"

USTRUCT(BlueprintType)
struct FCreateMatchmakingRuleSetRequest 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString RuleSetBody = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TMap<FString, FString> Tags = {};
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreateMatchmakingRuleSetResult, FMatchmakingRuleSet, MatchmakingRuleSet, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UCreateMatchmakingRuleSet_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "GameLift CreateMatchmakingRuleSet", meta = (BlueprintInternalUseOnly = "true"))
	static UCreateMatchmakingRuleSet_Async* CreateMatchmakingRuleSet(FCreateMatchmakingRuleSetRequest CreateMatchmakingRuleSetRequest);

	UPROPERTY(BlueprintAssignable)
	FOnCreateMatchmakingRuleSetResult Success;
	
	UPROPERTY(BlueprintAssignable)
	FOnCreateMatchmakingRuleSetResult Failure;

	virtual void ExecuteFailure(FGameLiftError Error) override;
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;

	FCreateMatchmakingRuleSetRequest Var_Request;
};
