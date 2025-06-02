// Fill out your copyright notice in the Description page of Project Settings.


#include "SMMainMenuGameMode.h"

#include "Blueprint/UserWidget.h"   // ���� ���� (����)
#include "Kismet/GameplayStatics.h" // ��Ʈ�ѷ� ��������

ASMMainMenuGameMode::ASMMainMenuGameMode()
{
    DefaultPawnClass = nullptr;
}

void ASMMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Ui Load �� ����
    if (TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/Menu/B_MainMenuWidget.B_MainMenuWidget_C")))
    {
        if (UUserWidget* MenuWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass))
        {
            MenuWidget->AddToViewport();
        }
    }

	//���콺 Ŀ�� ǥ��
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
    }
}
