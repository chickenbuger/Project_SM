// Fill out your copyright notice in the Description page of Project Settings.


#include "SMMainMenuGameMode.h"

#include "Blueprint/UserWidget.h"   // 위젯 관련 (생성)
#include "Kismet/GameplayStatics.h" // 컨트롤러 가져오기

ASMMainMenuGameMode::ASMMainMenuGameMode()
{
    DefaultPawnClass = nullptr;
}

void ASMMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	//Ui Load 및 생성
    if (TSubclassOf<UUserWidget> WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Widgets/Menu/B_MainMenuWidget.B_MainMenuWidget_C")))
    {
        if (UUserWidget* MenuWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass))
        {
            MenuWidget->AddToViewport();
        }
    }

	//마우스 커서 표시
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        PC->bShowMouseCursor = true;
        PC->SetInputMode(FInputModeUIOnly());
    }
}
