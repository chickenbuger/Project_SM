// Fill out your copyright notice in the Description page of Project Settings.


#include "SMPlayerInfo.h"
#include "Widgets/Common/SMHealthWidget.h"
#include "Components/TextBlock.h"

void USMPlayerInfo::NativeConstruct()
{
	Super::NativeConstruct();
}

void USMPlayerInfo::UpdateInfo(const float InMaxHP, float InNewHp)
{
	SetHealthPercent(InNewHp / InMaxHP);
}

void USMPlayerInfo::SetHealthPercent(float InPercent)
{
	if (HPBar)
	{
		HPBar->SetHealthPercent(InPercent);
	}
}

void USMPlayerInfo::SetPlayerName(const FString& Name)
{
	if (PlayerName)
	{
		PlayerName->SetText(FText::FromString(Name));
	}
}