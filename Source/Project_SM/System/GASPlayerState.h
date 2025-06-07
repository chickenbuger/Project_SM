// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GASPlayerState.generated.h"

/**
 * 
 */
class UHealthAttributeSet;

class UAbilitySystemComponent;

class ASMCharacter;

UCLASS()
class PROJECT_SM_API AGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AGASPlayerState();

public:
	// GAS ¼¼ÆÃ
	FORCEINLINE UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

public:
	UPROPERTY()
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;

	UPROPERTY(EditAnywhere)
	float InitialHealth = 100.0f; // I usually define this here but set its value in BP but for now we'll do both here

	const ASMCharacter* GetOwningPlayerCharacter() const;
	void SetOwningPlayerCharacter(ACharacter* InOwningCharacter);

protected:
	virtual void Init();

protected:
	UFUNCTION()
	void HandleHealthChanged(float Magnitude, float NewHealth);

private:
	UPROPERTY()
	TObjectPtr<ASMCharacter> OwningPlayerCharacter;
};
