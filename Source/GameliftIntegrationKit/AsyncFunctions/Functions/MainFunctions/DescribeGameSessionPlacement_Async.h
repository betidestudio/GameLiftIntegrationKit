// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AsyncFunctions/GameliftBaseFunction.h"
#include "DescribeGameSessionPlacement_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDescribeGameSessionPlacementOutput, const FGameSessionPlacement&, GameSessionPlacement, FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UDescribeGameSessionPlacement_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Describe Game Session Placement"), Category = "AWS Integration Kit|GameLift")
	static UDescribeGameSessionPlacement_Async* DescribeGameSessionPlacement(FString PlacementId);

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	FString Var_PlacementId;

	UPROPERTY(BlueprintAssignable)
	FOnDescribeGameSessionPlacementOutput Success;

	UPROPERTY(BlueprintAssignable)
	FOnDescribeGameSessionPlacementOutput Failure;
};
