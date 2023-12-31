﻿//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftObject.h"
#include "GameliftSharedClass.h"
#include "UObjectIterator.h"
#include "GameliftSharedClass.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameliftBaseFunction.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EGameLiftErrors
{
	//From Core//
	//////////////////////////////////////////////////////////////////////////////////////////
	INCOMPLETE_SIGNATURE = 0,
	INTERNAL_FAILURE = 1,
	INVALID_ACTION = 2,
	INVALID_CLIENT_TOKEN_ID = 3,
	INVALID_PARAMETER_COMBINATION = 4,
	INVALID_QUERY_PARAMETER = 5,
	INVALID_PARAMETER_VALUE = 6,
	MISSING_ACTION = 7, // SDK should never allow
	MISSING_AUTHENTICATION_TOKEN = 8, // SDK should never allow
	MISSING_PARAMETER = 9, // SDK should never allow
	OPT_IN_REQUIRED = 10,
	REQUEST_EXPIRED = 11,
	SERVICE_UNAVAILABLE = 12,
	THROTTLING = 13,
	VALIDATION = 14,
	ACCESS_DENIED = 15,
	RESOURCE_NOT_FOUND = 16,
	UNRECOGNIZED_CLIENT = 17,
	MALFORMED_QUERY_STRING = 18,
	SLOW_DOWN = 19,
	REQUEST_TIME_TOO_SKEWED = 20,
	INVALID_SIGNATURE = 21,
	SIGNATURE_DOES_NOT_MATCH = 22,
	INVALID_ACCESS_KEY_ID = 23,
	REQUEST_TIMEOUT = 24,
	NETWORK_CONNECTION = 99,

	UNKNOWN = 100,
	///////////////////////////////////////////////////////////////////////////////////////////

	CONFLICT= static_cast<int>(Aws::Client::CoreErrors::SERVICE_EXTENSION_START_RANGE) + 1,
	FLEET_CAPACITY_EXCEEDED,
	GAME_SESSION_FULL,
	IDEMPOTENT_PARAMETER_MISMATCH,
	INTERNAL_SERVICE,
	INVALID_FLEET_STATUS,
	INVALID_GAME_SESSION_STATUS,
	INVALID_REQUEST,
	LIMIT_EXCEEDED,
	NOT_FOUND,
	OUT_OF_CAPACITY,
	TAGGING_FAILED,
	TERMINAL_ROUTING_STRATEGY,
	UNAUTHORIZED,
	UNSUPPORTED_REGION
};

USTRUCT(BlueprintType)
struct FGameLiftError
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ErrorMessage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GetMessageA;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GetMessageW;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ExceptionName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EGameLiftErrors> ErrorType;
};
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UGameliftBaseFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	virtual void Activate() override;

	virtual void ContinueProcess(UGameliftObject* AWSObject);

	virtual void ExecuteFailure(FGameLiftError Error);
};
