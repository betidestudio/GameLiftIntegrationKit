//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UpdateMatchmakingConfiguration_Async.generated.h"

USTRUCT(BlueprintType)
struct FUpdateMatchmakingConfigurationRequest 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	bool bAcceptanceRequired = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 RequestTimeoutSeconds = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString RuleSetName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 AcceptanceTimeoutSeconds = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	int32 AdditionalPlayerCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EBackfillMode> BackfillMode = EBackfillMode::NOT_SET;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString CustomEventData = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString Description = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EFlexMatchMode> FlexMatchMode = EFlexMatchMode::NOT_SET1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FGameProperty> GameProperties = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FString> GameSessionQueueArns = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionData = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString NotificationTarget = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TMap<FString, FString> StringProperties = {};
	
};



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateMatchmakingConfigurationAsync, FMatchmakingConfiguration, Response, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UUpdateMatchmakingConfiguration_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Update Matchmaking Configuration"), Category = "AWS Integration Kit|GameLift")
	static UUpdateMatchmakingConfiguration_Async* UpdateMatchmakingConfiguration(FUpdateMatchmakingConfigurationRequest Request);

	virtual void ExecuteFailure(FGameLiftError Error) override;
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	
	UPROPERTY(BlueprintAssignable)
	FOnUpdateMatchmakingConfigurationAsync Success;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateMatchmakingConfigurationAsync Failure;

	FUpdateMatchmakingConfigurationRequest Var_Request;
};
