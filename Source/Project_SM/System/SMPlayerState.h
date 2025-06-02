// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "SMPlayerState.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;
class UHealthAttributeSet;

UCLASS()
class PROJECT_SM_API ASMPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ASMPlayerState();

public:
	void Init();

public:
	// GAS ¼¼ÆÃ
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

public:
	UPROPERTY()
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;

	UPROPERTY(EditAnywhere)
	float InitialHealth = 100.0f; // I usually define this here but set its value in BP but for now we'll do both here

	UFUNCTION()
	void HandleHealthChanged(float Magnitude, float NewHealth);
};
