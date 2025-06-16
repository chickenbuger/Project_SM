// Fill out your copyright notice in the Description page of Project Settings.


#include "SMMainMenuPlayerController.h"

#include "Blueprint/UserWidget.h"

void ASMMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController()) // ���� �÷��̾����� Ȯ��
	{
		// UI ���� �ε� �� ����
		if (TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/Menu/B_MainMenuWidget.B_MainMenuWidget_C")))
		{
			if (UUserWidget* MenuWidget = CreateWidget<UUserWidget>(this, WidgetClass))
			{
				MenuWidget->AddToViewport();
			}
		}

		// ���콺 Ŀ�� ǥ��
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}