//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AsyncFunctions/GameliftBaseFunction.h"
#include "CreateMatchmakingConfiguration_Async.generated.h"

USTRUCT(BlueprintType)
struct FCreateMatchmakingConfigurationRequest
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreateMatchmakingConfigurationAsync, FMatchmakingConfiguration, Response, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UCreateMatchmakingConfiguration_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", DisplayName = "Create Matchmaking Configuration"), Category = "AWS Integration Kit|GameLift")
	static UCreateMatchmakingConfiguration_Async* CreateMatchmakingConfiguration(FCreateMatchmakingConfigurationRequest Request);

	FCreateMatchmakingConfigurationRequest Var_Request;

	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	UPROPERTY(BlueprintAssignable)
	FOnCreateMatchmakingConfigurationAsync Success;

	UPROPERTY(BlueprintAssignable)
	FOnCreateMatchmakingConfigurationAsync Failure;
	
};
