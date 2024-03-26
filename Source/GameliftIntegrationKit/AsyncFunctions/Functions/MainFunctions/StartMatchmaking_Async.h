//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftIntegrationKit/AsyncFunctions/GameliftBaseFunction.h"
#include "StartMatchmaking_Async.generated.h"

USTRUCT(BlueprintType)
struct FStartMatchmakingRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString ConfigurationName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FGameliftPlayer> Players;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString TicketId;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartMatchmakingAsyncOutputPin, FMatchmakingTicket, Result, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UStartMatchmaking_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Start Matchmaking"), Category = "AWS Integration Kit|GameLift")
	static UStartMatchmaking_Async* StartMatchmaking(FStartMatchmakingRequest Request);

	
	FStartMatchmakingRequest Var_Request;

	UPROPERTY(BlueprintAssignable)
	FStartMatchmakingAsyncOutputPin Success;

	UPROPERTY(BlueprintAssignable)
	FStartMatchmakingAsyncOutputPin Failure;

	virtual void Activate() override;

	virtual void ExecuteFailure(FGameLiftError Error) override;
	void StartMatchmaking_Async();
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	
};
