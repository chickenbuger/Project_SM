// Fill out your copyright notice in the Description page of Project Settings.


#include "SMHostWidget.h"
#include "System/SMGameInstance.h"

#include "Components/Button.h"			// 버튼 바인딩
#include "Components/Checkbox.h"		// 체크 박스 바인딩

void USMHostWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 바인딩
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