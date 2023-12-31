//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AsyncFunctions/GameliftBaseFunction.h"
#include "AcceptMatch_Async.generated.h"

USTRUCT(BlueprintType)
struct FAcceptMatchRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	FString TicketId = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TArray<FString> PlayerId = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit|GameLift")
	TEnumAsByte<EAcceptanceType> AcceptanceType = EAcceptanceType::NOT_SET4;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAcceptMatchAsyncOutputPin, FGameLiftError, Error);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UAcceptMatch_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Accept Match"), Category = "AWS Integration Kit|GameLift")
	static UAcceptMatch_Async* AcceptMatch(FAcceptMatchRequest Request);
	
	FAcceptMatchRequest Var_Request;

	UPROPERTY(BlueprintAssignable)
	FAcceptMatchAsyncOutputPin Success;

	UPROPERTY(BlueprintAssignable)
	FAcceptMatchAsyncOutputPin Failure;

	virtual void ExecuteFailure(FGameLiftError Error) override;
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	
};
