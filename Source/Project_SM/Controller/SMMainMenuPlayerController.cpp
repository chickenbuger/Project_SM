// Fill out your copyright notice in the Description page of Project Settings.


#include "SMMainMenuPlayerController.h"

#include "Blueprint/UserWidget.h"

void ASMMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController()) // 로컬 플레이어인지 확인
	{
		// UI 위젯 로드 및 생성
		if (TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/Menu/B_MainMenuWidget.B_MainMenuWidget_C")))
		{
			if (UUserWidget* MenuWidget = CreateWidget<UUserWidget>(this, WidgetClass))
			{
				MenuWidget->AddToViewport();
			}
		}

		// 마우스 커서 표시
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}