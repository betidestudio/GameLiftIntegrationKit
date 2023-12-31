// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AsyncFunctions/GameliftBaseFunction.h"
#include "StopGameSessionPlacement_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStopGameSessionPlacementOutput, const FGameSessionPlacement&, GameSessionPlacement, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UStopGameSessionPlacement_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Stop Game Session Placement"), Category = "AWS Integration Kit|GameLift")
	static UStopGameSessionPlacement_Async* StopGameSessionPlacement(FString PlacementId);

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	FString Var_PlacementId;

	UPROPERTY(BlueprintAssignable)
	FOnStopGameSessionPlacementOutput Success;

	UPROPERTY(BlueprintAssignable)
	FOnStopGameSessionPlacementOutput Failure;
};
