// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// Online
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "SMGameInstance.generated.h"

/**
 * 
 */
class USMSearchContentWidget;

USTRUCT(BlueprintType)
struct FSessionInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString SessionName;

    UPROPERTY(BlueprintReadOnly)
    FString HostName;

    UPROPERTY(BlueprintReadOnly)
    int32 CurrentPlayers;

    UPROPERTY(BlueprintReadOnly)
    int32 MaxPlayers;

    int32 SessionIndex; // 郴何侩
};

UCLASS()
class PROJECT_SM_API USMGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    virtual void Init() override;

    //void DestroyAndCreateSession();         // 技记 颇鲍 饶 积己
    void CreateSession();                   // 技记 积己
    void FindSession();                     // 技记 八祸
    //void JoinSession(const FOnlineSessionSearchResult& Result);     // 技记 曼啊

public:
    UPROPERTY(BlueprintReadOnly)
    TArray<FSessionInfo> SearchResultsList;

    UPROPERTY()
    USMSearchContentWidget* SearchWidget;

private:
    // 妮归 勤甸矾
    void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
    void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
    void OnFindSessionsComplete(bool bWasSuccessful);
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
    IOnlineSessionPtr SessionInterface;
    TSharedPtr<FOnlineSessionSearch> SessionSearch;

    FOnCreateSessionCompleteDelegate    OnCreateSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate   OnDestroySessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate     OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate      OnJoinSessionCompleteDelegate;
};
