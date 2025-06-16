// Fill out your copyright notice in the Description page of Project Settings.


#include "SMHostWidget.h"
#include "System/SMGameInstance.h"

#include "Components/Button.h"			// ��ư ���ε�
#include "Components/Checkbox.h"		// üũ �ڽ� ���ε�

void USMHostWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư ���ε�
	{
		if (Btn_Create)
		{
			Btn_Create->OnClicked.AddUniqueDynamic(this, &ThisClass::OnCreateSessionClicked);
		}
	}
}

void USMHostWidget::OnCreateSessionClicked()
{
	USMGameInstance* GI = GetGameInstance<USMGameInstance>();
	if (!GI) return;
	
	GI->CreateSession();
}