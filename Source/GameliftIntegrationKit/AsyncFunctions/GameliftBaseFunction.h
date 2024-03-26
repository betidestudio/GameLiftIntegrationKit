//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameliftObject.h"
#include "GameliftSharedClass.h"
#include "UObject/UObjectIterator.h"
#include "GameliftSharedClass.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GenericPlatformProcess.h"
#include "GameliftBaseFunction.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EGameLiftErrors
{
	ALREADY_INITIALIZED,             // The GameLift Server or Client has already been initialized with
                                     // Initialize().
    FLEET_MISMATCH,                  // The target fleet does not match the fleet of a gameSession or playerSession.
    GAMELIFT_CLIENT_NOT_INITIALIZED, // The GameLift client has not been initialized.
    GAMELIFT_SERVER_NOT_INITIALIZED, // The GameLift server has not been initialized.
    GAME_SESSION_ENDED_FAILED,       // The GameLift Server SDK could not contact the service to report
                                     // the game session ended.
    GAME_SESSION_NOT_READY,          // The GameLift Server Game Session was not activated.
    GAME_SESSION_READY_FAILED,       // The GameLift Server SDK could not contact the service to report
                                     // the game session is ready.
    GAME_SESSION_ID_NOT_SET,         // No game sessions are bound to this process.
    INITIALIZATION_MISMATCH,         // A client method was called after Server::Initialize(), or vice
                                     // versa.
    NOT_INITIALIZED,                 // The GameLift Server or Client has not been initialized with Initialize().
    NO_TARGET_ALIASID_SET,           // A target aliasId has not been set.
    NO_TARGET_FLEET_SET,             // A target fleet has not been set.
    PROCESS_ENDING_FAILED,           // The GameLift Server SDK could not contact the service to report the
                                     // process is ending.
    PROCESS_NOT_ACTIVE,              // The server process is not yet active, not bound to a GameSession, and
                                     // cannot accept or process PlayerSessions.
    PROCESS_NOT_READY,               // The server process is not yet ready to be activated.
    PROCESS_READY_FAILED,            // The GameLift Server SDK could not contact the service to report the
                                     // process is ready.
    SDK_VERSION_DETECTION_FAILED,    // SDK version detection failed.
    SERVICE_CALL_FAILED,             // A call to an AWS service has failed.
    STX_CALL_FAILED,                 // A call to the XStx server backend component has failed.
    STX_INITIALIZATION_FAILED,       // The XStx server backend component has failed to initialize.
    UNEXPECTED_PLAYER_SESSION,       // An unregistered player session was encountered by the server.
    BAD_REQUEST_EXCEPTION,
    INTERNAL_SERVICE_EXCEPTION,
    WEBSOCKET_CONNECT_FAILURE,                // Failure to connect to the GameLift Service WebSocket
    WEBSOCKET_CONNECT_FAILURE_FORBIDDEN,      // Access denied, e.g. auth token has expired
    WEBSOCKET_CONNECT_FAILURE_INVALID_URL,    // End point URL is invalid
    WEBSOCKET_CONNECT_FAILURE_TIMEOUT,        // Timeout
    WEBSOCKET_RETRIABLE_SEND_MESSAGE_FAILURE, // Retriable failure to send message to the GameLift
                                              // Service WebSocket
    WEBSOCKET_SEND_MESSAGE_FAILURE            // Failure to send message to the GameLift Service WebSocket
};

USTRUCT(BlueprintType)
struct FGameLiftError
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameLift Integration Kit")
	FString ErrorMessage = "GameLiftError";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameLift Integration Kit")
	FString GetMessageA = "GameLiftError";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameLift Integration Kit")
	FString GetMessageW = "GameLiftError";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameLift Integration Kit")
	FString ExceptionName = "GameLiftError";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GameLift Integration Kit")
	TEnumAsByte<EGameLiftErrors> ErrorType = EGameLiftErrors::UNEXPECTED_PLAYER_SESSION;
};


UCLASS()
class GAMELIFTINTEGRATIONKIT_API UGameliftBaseFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	virtual void Activate() override;

	virtual void ContinueProcess(UGameliftObject* AWSObject);

	virtual void ExecuteFailure(FGameLiftError Error);
	
	virtual void SetReadyToDestroy() override
	{
		Super::SetReadyToDestroy();
		RemoveFromRoot();
	}
};
