// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"    
#include "AbilitySystem/Attributes/PlayBaseAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "HealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SM_API UHealthAttributeSet : public UPlayBaseAttributeSet
{
	GENERATED_BODY()
	
public:
    void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

    UPROPERTY()
    FPlayAttributeEvent OnHealthChanged;

    UPROPERTY(BlueprintReadOnly, Category = "Attributes")
    FGameplayAttributeData Health;
    PLAY_ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health);
};
