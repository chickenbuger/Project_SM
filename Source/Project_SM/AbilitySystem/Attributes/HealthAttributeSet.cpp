// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAttributeSet.h"
#include "GameplayEffectExtension.h"

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	float OldValue = Health.GetCurrentValue();
	float NewValue = FMath::Clamp(OldValue + Data.EvaluatedData.Magnitude, 0.0f, Health.GetBaseValue());
	SetHealth(NewValue);
	float Delta = NewValue - OldValue;

	OnHealthChanged.Broadcast(Delta, NewValue);
}
