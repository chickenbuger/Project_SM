// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SMPlayerInfo.generated.h"

/**
 * 
 */
class UTextBlock;
class USMHealthWidget;

UCLASS()
class PROJECT_SM_API USMPlayerInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	//변경점이 체력밖에 없음
	void UpdateInfo(const float InMaxHP, float InNewHp);

	UFUNCTION(BlueprintCallable)
	void SetHealthPercent(float InPercent);

		UFUNCTION(BlueprintCallable)
	void SetPlayerName(const FString& Name);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USMHealthWidget> HPBar;
};
