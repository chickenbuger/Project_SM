// Fill out your copyright notice in the Description page of Project Settings.


#include "SMMainMenuWidget.h"			// 자신 헤더
#include "Kismet/GameplayStatics.h"		// 레벨 이동
#include "Components/Button.h"			// 버튼 바인딩

void USMMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 바인딩
	{
		if (Btn_SinglePlay)
		{
			Btn_SinglePlay->OnClicked.AddUniqueDynamic(this, &ThisClass::OnSingleGamePlayClicked);
		}

		if (Btn_MultiPlay)
		{
			Btn_MultiPlay->OnClicked.AddUniqueDynamic(this, &ThisClass::OnMultiGamePlayClicked);
		}
	}
}

void USMMainMenuWidget::OnSingleGamePlayClicked()
{
	UGameplayStatics::OpenLevel(this, FName("TestMap"),true,TEXT("?game=/Game/Game/B_SMGameMode.B_SMGameMode_C"));
}

void USMMainMenuWidget::OnMultiGamePlayClicked()
{
	UGameplayStatics::OpenLevel(this, FName("TestMap"));
}
