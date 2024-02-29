//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DeleteMatchmakingConfiguration_Async.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeleteMatchmakingConfigurationAsync, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UDeleteMatchmakingConfiguration_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Delete Matchmaking Configuration"), Category = "AWS Integration Kit|GameLift")
	static UDeleteMatchmakingConfiguration_Async* DeleteMatchmakingConfiguration(FString Name);

	FString Var_Name;

	UPROPERTY(BlueprintAssignable)
	FOnDeleteMatchmakingConfigurationAsync Success;

	UPROPERTY(BlueprintAssignable)
	FOnDeleteMatchmakingConfigurationAsync Failure;

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;
};
