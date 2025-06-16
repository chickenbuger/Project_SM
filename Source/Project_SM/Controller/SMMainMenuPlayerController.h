// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SMMainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SM_API ASMMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
