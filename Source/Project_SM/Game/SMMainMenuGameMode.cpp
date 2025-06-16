// Fill out your copyright notice in the Description page of Project Settings.


#include "SMMainMenuGameMode.h"

#include "Controller/SMMainMenuPlayerController.h"

ASMMainMenuGameMode::ASMMainMenuGameMode()
{
    DefaultPawnClass = nullptr;
    PlayerControllerClass = ASMMainMenuPlayerController::StaticClass();
}