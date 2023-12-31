//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AsyncFunctions/GameliftBaseFunction.h"
#include "StartMatchBackfill_Async.generated.h"


USTRUCT(BlueprintType)
struct FStartMatchBackfillRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString ConfigurationName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FGameliftPlayer> Players;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString GameSessionArn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString TicketId;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartMatchBackfillAsyncOutputPin, FMatchmakingTicket, Result, FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UStartMatchBackfill_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Start Match Backfill"), Category = "AWS Integration Kit|GameLift")
	static UStartMatchBackfill_Async* StartMatchBackfill(FStartMatchBackfillRequest Request);
	
	
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;
	
	UPROPERTY(BlueprintAssignable)
	FStartMatchBackfillAsyncOutputPin Success;

	UPROPERTY(BlueprintAssignable)
	FStartMatchBackfillAsyncOutputPin Failure;

	FStartMatchBackfillRequest Var_Request;

	
};
