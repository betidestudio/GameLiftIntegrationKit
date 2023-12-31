// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AsyncFunctions/GameliftBaseFunction.h"
#include "UpdateGameSession_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateGameSessionSuccess, const FGLGameSession&, GameSession, FGameLiftError, Error);
UCLASS()
class GAMELIFTINTEGRATIONKIT_API UUpdateGameSession_Async : public UGameliftBaseFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true",DisplayName="Update Game Session"), Category = "AWS Integration Kit|GameLift")
	static UUpdateGameSession_Async* UpdateGameSession(const TArray<FGameProperty>& GameProperties, const FString& GameSessionId, int32 MaximumPlayerSessionCount, const FString& Name, EPlayerSessionCreationPolicy PlayerSessionCreationPolicy, EProtectionPolicy ProtectionPolicy);
	
	virtual void ContinueProcess(UGameliftObject* AWSObject) override;
	virtual void ExecuteFailure(FGameLiftError Error) override;

	TArray<FGameProperty> Var_GameProperties;
	FString Var_GameSessionId;
	int32 Var_MaximumPlayerSessionCount;
	FString Var_Name;
	TEnumAsByte<EPlayerSessionCreationPolicy> Var_PlayerSessionCreationPolicy;
	TEnumAsByte<EProtectionPolicy> Var_ProtectionPolicy;

	UPROPERTY(BlueprintAssignable)
		FOnUpdateGameSessionSuccess Success;

	UPROPERTY(BlueprintAssignable)
		FOnUpdateGameSessionSuccess Failure;
	
};
