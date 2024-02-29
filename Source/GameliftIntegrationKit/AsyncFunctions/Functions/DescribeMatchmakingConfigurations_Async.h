//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DescribeMatchmakingConfigurations_Async.generated.h"


USTRUCT(BlueprintType)
struct FDescribeMatchmakingConfigurationsRequest
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FString> Names = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString RuleSetName = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 Limit = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString NextToken = "";
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDescribeMatchmakingConfigurationsAsync, const TArray<FMatchmakingConfiguration>&, MatchmakingConfigurations, const FString&, NextToken, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UDescribeMatchmakingConfigurations_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Describe Matchmaking Configurations"), Category = "AWS Integration Kit|GameLift")
	static UDescribeMatchmakingConfigurations_Async* DescribeMatchmakingConfigurations(FDescribeMatchmakingConfigurationsRequest Request);
	
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	UPROPERTY(BlueprintAssignable)
	FOnDescribeMatchmakingConfigurationsAsync Success;

	UPROPERTY(BlueprintAssignable)
	FOnDescribeMatchmakingConfigurationsAsync Failure;

	FDescribeMatchmakingConfigurationsRequest Var_Request;
	
};
