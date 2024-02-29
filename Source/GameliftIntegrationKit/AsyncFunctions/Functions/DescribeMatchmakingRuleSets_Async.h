//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "DescribeMatchmakingRuleSets_Async.generated.h"

USTRUCT(BlueprintType)
struct FDescribeMatchmakingRuleSetsRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FString> Names = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 Limit = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString NextToken = "";
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDescribeMatchmakingRuleSetsAsync, TArray<FMatchmakingRuleSet>, Response, FString, NextToken, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UDescribeMatchmakingRuleSets_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", DisplayName = "Describe Matchmaking RuleSets"), Category = "AWS Integration Kit|GameLift")
	static UDescribeMatchmakingRuleSets_Async* DescribeMatchmakingRuleSets(FDescribeMatchmakingRuleSetsRequest Request);

	FDescribeMatchmakingRuleSetsRequest Var_Request;

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;
	
	
	UPROPERTY(BlueprintAssignable)
	FOnDescribeMatchmakingRuleSetsAsync Success;

	UPROPERTY(BlueprintAssignable)
	FOnDescribeMatchmakingRuleSetsAsync Failure;

	
	
};
