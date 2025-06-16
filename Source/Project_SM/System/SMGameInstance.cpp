// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGameInstance.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "Online/OnlineSessionNames.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

#include "Widgets/MainMenu/SMSearchContentWidget.h"

void USMGameInstance::Init()
{
    Super::Init();

    IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
    if (Subsystem)
    {
        SessionInterface = Subsystem->GetSessionInterface();
        if(SessionInterface.IsValid())
        {
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &USMGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &USMGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &USMGameInstance::OnJoinSessionComplete);
        }
    }
}
/*
void USMGameInstance::DestroyAndCreateSession()
{

    if (!SessionInterface.IsValid()) return;

    if (SessionInterface->GetNamedSession(NAME_GameSession))
    {
        SessionInterface->DestroySession(NAME_GameSession);
    }
    else
    {
        CreateSession();
    }
}
*/

void USMGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        CreateSession();
    }
}

void USMGameInstance::CreateSession()
{
    if (!SessionInterface.IsValid()) return;

    /**
     *	NAME_GameSession - 전역 변수
     *	기존에 세션이 있는지 확인한다.
     *	만약 세션이 있다면 NAME_GameSession에 해당하는 세션을 파괴한다.
     *	CreateSessionCompleteDelegate_Handle에 콜백함수를 바인딩해준다.
     **/


    const auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession); // 
    if (ExistingSession != nullptr)
    {
        SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(
            FOnDestroySessionCompleteDelegate::CreateUObject(this, &USMGameInstance::OnDestroySessionComplete));
        SessionInterface->DestroySession(NAME_GameSession);
        return;
    }

    /**
     *	#include "OnlineSessionSettings.h"
     *	SessionSettings를 공유포인터로 생성해준다.
     *	SessionSettings 설정
     *	OnlineSessionInterface -> CreateSession의 argument를 넣어준다
     */
    //TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
    FOnlineSessionSettings SessionSettings;
    SessionSettings.bAllowJoinInProgress = true;	// 세션이 실행 중(게임 중) 참여가능 여부
	SessionSettings.bIsDedicated = false;		    // 세션이 Dedicated Server인지 여부
    SessionSettings.bIsLANMatch = true;			    // Steam을 사용할 것이기 때문에 LanMatch = false
    SessionSettings.bShouldAdvertise = true;		// Steam을 통해 세션을 알린다.(다른 플레이어가 해당 세션을 찾아 참여 가능)
    SessionSettings.bUsesPresence = true;			// 정확하지 않음 - Steam 사용자와 같은 지역에서 세션을 찾을 수 있는 여부
    SessionSettings.NumPublicConnections = 4;		// 세션에 연결 가능한 인원

	SessionInterface->CreateSession(0, FName("My Session"), SessionSettings);

    //SessionSettings->Set(FName("MatchType"), FString("FreeForAll"), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

    //const ULocalPlayer* Localplayer = GetWorld()->GetFirstLocalPlayerFromController();
    //UE_LOG(LogTemp, Warning, TEXT("Create PreferredUniqueNetId %s"), *Localplayer->GetPreferredUniqueNetId()->ToString());
    //SessionInterface->CreateSession(*Localplayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings);
}

void USMGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
		UWorld* World = GetWorld();
        if (World)
        {
			World->ServerTravel("/Game/Level/TestMap?listen");
        }
        else
        {
			UE_LOG(LogTemp, Warning, TEXT("Failed to create session: %s"), *SessionName.ToString());
        }
    }
}
void USMGameInstance::FindSession()
{
    if (!SessionInterface.IsValid()) return;

    SessionSearch = MakeShareable(new FOnlineSessionSearch());

    SessionSearch->bIsLanQuery = true;
    SessionSearch->MaxSearchResults = 100;
    SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); 

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
    //const ULocalPlayer* Localplayer = GetWorld()->GetFirstLocalPlayerFromController();
    //UE_LOG(LogTemp, Warning, TEXT("Join PreferredUniqueNetId %s"), *Localplayer->GetPreferredUniqueNetId()->ToString());
    //SessionInterface->FindSessions(*Localplayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
}

void USMGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
    UE_LOG(LogTemp, Warning, TEXT("OnFindSessionComplete"));
    if (bWasSuccessful)
    {
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;

        if (SearchResults.Num())
        {
			SessionInterface->JoinSession(0, "My Session", SearchResults[0]);
        }
    }

}
/*
void USMGameInstance::JoinSession(const FOnlineSessionSearchResult& Result)
{
    if (!SessionInterface.IsValid()) return;

    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    SessionSearch->MaxSearchResults = 20;
    SessionSearch->bIsLanQuery = false;
    //SessionSearch->QuerySettings.Set(FName("presence"), true, EOnlineComparisonOp::Equals); //EOS 온라인 체크

    SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}
*/

void USMGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    if (!SessionInterface.IsValid()) return;

    if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        FString Address = "";
        SessionInterface->GetResolvedConnectString(SessionName, Address);
        if (Address != "")
        {
            PController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
        }
    }
}
