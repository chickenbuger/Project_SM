// Fill out your copyright notice in the Description page of Project Settings.


#include "SMMainMenuWidget.h"			// �ڽ� ���
#include "Kismet/GameplayStatics.h"		// ���� �̵�
#include "Components/Button.h"			// ��ư ���ε�

void USMMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư ���ε�
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
