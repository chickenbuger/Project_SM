// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SMPlayerController.generated.h"


/**
 * 
 */
class ASMCharacter;

UCLASS()
class PROJECT_SM_API ASMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASMPlayerController();

public:
	void SetPlayerCharacter(ASMCharacter* InCharacter);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MouseClickAction;

	UFUNCTION()
	void OnMouseClick(const FInputActionValue& Value);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	ASMCharacter* PlayerCharacter;

private:
	void SwapControllerToAIController(APawn* InPawn);
};
