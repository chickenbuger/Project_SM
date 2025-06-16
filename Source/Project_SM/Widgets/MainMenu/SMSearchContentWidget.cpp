// Fill out your copyright notice in the Description page of Project Settings.


#include "SMSearchContentWidget.h"
#include "SMJoinSessionListWidget.h"
#include "System/SMGameInstance.h"

#include "Components/Button.h"	
#include "Components/ScrollBox.h"	

void USMSearchContentWidget::CallBack_FindSessionResult()
{
	USMGameInstance* GI = GetGameInstance<USMGameInstance>();
	if (!GI) return;

 	TArray<FSessionInfo> SessionInfo = GI->SearchResultsList;

	for (const FSessionInfo& info : SessionInfo)
	{
		// Session Widget 추가 
	}

	Btn_Find->SetIsEnabled(true);
}

void USMSearchContentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 바인딩
	{
		if (Btn_Find)
		{
			Btn_Find->OnClicked.AddUniqueDynamic(this, &ThisClass::OnFindSession);
		}
	}
}

void USMSearchContentWidget::OnFindSession()
{
	USMGameInstance* GI = GetGameInstance<USMGameInstance>();
	if (!GI) return;

	SessionScroll->ClearChildren();

	Btn_Find->SetIsEnabled(false);

	GI->SearchWidget = this;
	GI->FindSession();
}
