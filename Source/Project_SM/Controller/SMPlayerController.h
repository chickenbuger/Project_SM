// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SMPlayerController.generated.h"


/**
 * 
 */

class UInputAction;
class ASMCharacter;

UCLASS()
class PROJECT_SM_API ASMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASMPlayerController();

public:
	/** Setter Player Character -> SMCharacter*/
	void SetPlayerCharacter(ASMCharacter* InCharacter);

	/** Getter Player Character -> SMCharacter*/
	UFUNCTION(BlueprintCallable)
	ASMCharacter* GetPlayerCharacter() const { return PlayerCharacter; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MouseClickAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* TestClickAction;

	// MouseClickAction
	UFUNCTION()
	void OnMouseClick(const FInputActionValue& Value);

	// TestClickAction
	UFUNCTION()
	void OnTestClick(const FInputActionValue& Value);

	virtual void BeginPlay() override;
	virtual void SetupInputComponent();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	ASMCharacter* PlayerCharacter;

private:
	void SwapControllerToAIController(APawn* InPawn);

	void SetupCharacterInput();
};
