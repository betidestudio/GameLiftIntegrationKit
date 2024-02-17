//Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "aws/core/client/ClientConfiguration.h"
#include "aws/gamelift/GameLiftClient.h"
#include "GameliftObject.generated.h"

UENUM(BlueprintType)
enum EGameliftScheme
{
	HTTP,
	HTTPS
};

USTRUCT(BlueprintType)
struct FOtherGameliftSettings
{
	GENERATED_BODY()

	
	//Override the default client configuration. If you set this, all other settings in this struct will be used.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	bool bOverrideDefaultClientConfig = false;

	
	//User Agent string user for http calls. This is filled in for you in the constructor. Don't override this unless you have a really good reason.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString UserAgent;

	//Http scheme to use. E.g. Http or Https. Default HTTPS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	TEnumAsByte<EGameliftScheme> Scheme = EGameliftScheme::HTTPS;

	//Use dual stack endpoint in the endpoint calculation. It is your responsibility to verify that the service supports ipv6 in the region you select.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	bool bUseDualStack = false;

	//Use FIPS endpoint in the endpoint calculation. Please check first that the service supports FIPS in a selected region.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	bool bUseFIPS = false;

	//Max concurrent tcp connections for a single http client to use. Default 25.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	int32 MaxConnections = 25;

	/**
	* This is currently only applicable for Curl to set the http request level timeout, including possible dns lookup time, connection establish time, ssl handshake time and actual data transmission time.
	* the corresponding Curl option is CURLOPT_TIMEOUT_MS
	* defaults to 0, no http request level timeout.
	**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	int32 HttpRequestTimeoutMs = 0;

	/**
	* Socket read timeouts for HTTP clients on Windows. Default 3000 ms. This should be more than adequate for most services. However, if you are transferring large amounts of data
	* or are worried about higher latencies, you should set to something that makes more sense for your use case.
	* For Curl, it's the low speed time, which contains the time in number milliseconds that transfer speed should be below "lowSpeedLimit" for the library to consider it too slow and abort.
	* Note that for Curl this config is converted to seconds by rounding down to the nearest whole second except when the value is greater than 0 and less than 1000. In this case it is set to one second. When it's 0, low speed limit check will be disabled.
	* Note that for Windows when this config is 0, the behavior is not specified by Windows.
	**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	int32 RequestTimeoutMs = 0;

	//Socket connect timeout. Default 1000 ms. Unless you are very far away from your the data center you are talking to, 1000ms is more than sufficient.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	int32 ConnectTimeoutMs = 1000;

	/**
	* Enable TCP keep-alive. Default true;
	* No-op for WinHTTP, WinINet and IXMLHTTPRequest2 client.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	bool bEnableTCPKeepAlive = true;

	/**
	* Interval to send a keep-alive packet over the connection. Default 30 seconds. Minimum 15 seconds.
	* WinHTTP & libcurl support this option. Note that for Curl, this value will be rounded to an integer with second granularity.
	* No-op for WinINet and IXMLHTTPRequest2 client.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	int32 TCPKeepAliveIntervalMS = 30000;

	/**
	* Average transfer speed in bytes per second that the transfer should be below during the request timeout interval for it to be considered too slow and abort.
	* Default 1 byte/second. Only for CURL client currently.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	int32 LowSpeedLimit = 1;

	//Override the http endpoint used to talk to a service.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString EndpointOverride;

	//Allow HTTP client to discover system proxy setting. Off by default for legacy reasons.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	bool bAllowSystemProxy = false;

	//If you have users going through a proxy, set the proxy scheme here. Default HTTP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	TEnumAsByte<EGameliftScheme> ProxyScheme = EGameliftScheme::HTTP;

	//If you have users going through a proxy, set the host here.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString ProxyHost;

	//If you have users going through a proxy, set the port here.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	int32 ProxyPort = 0;

	//If you have users going through a proxy, set the username here.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString ProxyUsername;

	//If you have users going through a proxy, set the password here.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString ProxyPassword;

	/**
	* SSL Certificate file to use for connecting to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_SSLCERT in libcurl. Example: client.pem
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString ProxySSLCertPath;

	/**
	* Type of proxy client SSL certificate.
	* Used to set CURLOPT_PROXY_SSLCERTTYPE in libcurl. Example: PEM
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString ProxySSLCertType;

	/**
	* Private key file to use for connecting to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_SSLKEY in libcurl. Example: key.pem
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString ProxySSLKeyPath;
	
	/**
	* Type of private key file used to connect to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_SSLKEYTYPE in libcurl. Example: PEM
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString ProxySSLKeyType;

	/**
	* Passphrase to the private key file used to connect to an HTTPS proxy.
	* Used to set CURLOPT_PROXY_KEYPASSWD in libcurl. Example: password1
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString ProxySSLKeyPassword;

	//Calls to hosts in this vector will not use proxy configuration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	TArray<FString> NoProxyHosts;

	/**
	* If you need to test and want to get around TLS validation errors, do that here.
	* You probably shouldn't use this flag in a production scenario.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	bool bVerifyPeer = true;
};

USTRUCT(BlueprintType)
struct FAwsCredentials
{
	GENERATED_BODY()

	//AWS Access Key ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString AccessKeyId;

	//AWS Secret Access Key
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString SecretAccessKey;

	//AWS Session Token
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString SessionToken;
};

USTRUCT(BlueprintType)
struct FGameLiftSetup
{
	GENERATED_BODY()

	//AWS Region to use in signing requests. Default us-east-1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FString Region = "us-east-1";
	
	//Extra Non-Standard settings for the client. You probably don't need to change these.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FOtherGameliftSettings OtherSettings;

	//AWS Credentials to use in signing requests. If you leave these blank, the default credentials provider chain will be used.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AWS Integration Kit")
	FAwsCredentials Credentials;	
};



DECLARE_DYNAMIC_DELEGATE_OneParam(FOnGameliftSetupSuccess, bool, bIsSuccess);

UCLASS()
class GAMELIFTINTEGRATIONKIT_API UGameliftObject : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit", meta=(WorldContext="WorldContextObject"))
	static void InitGameLift(UObject* WorldContextObject, FGameLiftSetup Settings, FOnGameliftSetupSuccess OnGameliftSetupSuccess);

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit", meta=(WorldContext="WorldContextObject"))
	static bool ShutdownGameLift(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AWS Integration Kit", meta=(WorldContext="WorldContextObject"))
	static void SetupServer(UObject* WorldContextObject);
	
	Aws::Client::ClientConfiguration* Var_ClientConfig = nullptr;
	Aws::GameLift::GameLiftClient* Var_GameLiftClient = nullptr;
	FGameLiftSetup GameLiftSetup;

	
};
