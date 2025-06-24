// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGameInstance.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "Online/OnlineSessionNames.h"
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

    UE_LOG(LogTemp, Warning, TEXT("NetMode: %d"), GetWorld()->GetNetMode());

    const auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession); // 
    if (ExistingSession != nullptr)
    {
        SessionInterface->AddOnDestroySessionCompleteDelegate_Handle(
            FOnDestroySessionCompleteDelegate::CreateUObject(this, &USMGameInstance::OnDestroySessionComplete));
        SessionInterface->DestroySession(NAME_GameSession);
        return;
    }

    TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bAllowJoinInProgress = true;	// 게임 중에도 참여 가능
	SessionSettings->bIsLANMatch = true;		    // LAN 게임으로 설정  
	SessionSettings->NumPublicConnections = 4;	    // 최대 플레이어 수 설정
    SessionSettings->bShouldAdvertise = true;	    // 검색 허용

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	//SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), FName("GameSession"), *SessionSettings);
	SessionInterface->CreateSession(0, FName("GameSession"), *SessionSettings);
}

void USMGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            ENetMode NetMode = World->GetNetMode();

            switch (NetMode)
            {
            case NM_ListenServer:
            case NM_DedicatedServer:
                UE_LOG(LogTemp, Log, TEXT("[OnCreateSessionComplete] Running as server. Starting ServerTravel."));
                //World->ServerTravel("/Game/Level/TestMap?listen");
                break;

            case NM_Client:
                UE_LOG(LogTemp, Warning, TEXT("[OnCreateSessionComplete] Running as client - ServerTravel not allowed here."));
                break;

            case NM_Standalone:
                UE_LOG(LogTemp, Warning, TEXT("[OnCreateSessionComplete] Running as standalone - probably testing in editor."));
                break;

            default:
                UE_LOG(LogTemp, Warning, TEXT("[OnCreateSessionComplete] Unknown NetMode."));
                break;
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("[OnCreateSessionComplete] World is null."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[OnCreateSessionComplete] Session creation failed."));
    }
}

void USMGameInstance::FindSession()
{
    if (!SessionInterface.IsValid()) return;

    UE_LOG(LogTemp, Warning, TEXT("NetMode: %d"), GetWorld()->GetNetMode());

    SessionSearch = MakeShareable(new FOnlineSessionSearch());

    SessionSearch->bIsLanQuery = true;
    SessionSearch->MaxSearchResults = 100;
    //SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); 

    const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();

	//SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void USMGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
    if (bWasSuccessful && SessionSearch.IsValid())
    {
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;

        if (SearchResults.Num())
        {
            SessionInterface->JoinSession(0, FName("GameSession"), SearchResults[0]);
        }
    }

}

void USMGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
    if (!SessionInterface.IsValid()) return;

    UE_LOG(LogTemp, Log, TEXT("[OnJoinSessionComplete] Result: %d"), static_cast<int32>(Result));

    if (Result == EOnJoinSessionCompleteResult::Success)
    {
        if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
        {
            FString Address;
            if (SessionInterface->GetResolvedConnectString(SessionName, Address) && !Address.IsEmpty())
            {
                UE_LOG(LogTemp, Log, TEXT("[OnJoinSessionComplete] Traveling to %s"), *Address);
                PController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("[OnJoinSessionComplete] Failed to get connect string."));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[OnJoinSessionComplete] Join session failed."));
    }
}
