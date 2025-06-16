// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SMHostWidget.generated.h"

/**
 * 
 */
class UCheckBox;
class UButton;

UCLASS()
class PROJECT_SM_API USMHostWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCreateSessionClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> CB_LAN;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Create;
};
