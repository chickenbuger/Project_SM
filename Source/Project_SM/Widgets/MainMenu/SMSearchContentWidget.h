// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SMSearchContentWidget.generated.h"

/**
 * 
 */
class UButton;
class UScrollBox;
class USMJoinSessionListWidget;

UCLASS()
class PROJECT_SM_API USMSearchContentWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<USMJoinSessionListWidget> listWidget;

public:
	void CallBack_FindSessionResult();

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Btn_Find;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> SessionScroll;

private:
	UFUNCTION()
	void OnFindSession();
};
