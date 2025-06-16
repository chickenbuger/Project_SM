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
     *	NAME_GameSession - ���� ����
     *	������ ������ �ִ��� Ȯ���Ѵ�.
     *	���� ������ �ִٸ� NAME_GameSession�� �ش��ϴ� ������ �ı��Ѵ�.
     *	CreateSessionCompleteDelegate_Handle�� �ݹ��Լ��� ���ε����ش�.
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
     *	SessionSettings�� ���������ͷ� �������ش�.
     *	SessionSettings ����
     *	OnlineSessionInterface -> CreateSession�� argument�� �־��ش�
     */
    //TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
    FOnlineSessionSettings SessionSettings;
    SessionSettings.bAllowJoinInProgress = true;	// ������ ���� ��(���� ��) �������� ����
	SessionSettings.bIsDedicated = false;		    // ������ Dedicated Server���� ����
    SessionSettings.bIsLANMatch = true;			    // Steam�� ����� ���̱� ������ LanMatch = false
    SessionSettings.bShouldAdvertise = true;		// Steam�� ���� ������ �˸���.(�ٸ� �÷��̾ �ش� ������ ã�� ���� ����)
    SessionSettings.bUsesPresence = true;			// ��Ȯ���� ���� - Steam ����ڿ� ���� �������� ������ ã�� �� �ִ� ����
    SessionSettings.NumPublicConnections = 4;		// ���ǿ� ���� ������ �ο�

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
    //SessionSearch->QuerySettings.Set(FName("presence"), true, EOnlineComparisonOp::Equals); //EOS �¶��� üũ

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
