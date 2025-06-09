// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SMMainMenuWidget.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class PROJECT_SM_API USMMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnSingleGamePlayClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_SinglePlay;
};
