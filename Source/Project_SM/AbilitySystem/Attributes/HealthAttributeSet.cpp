// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAttributeSet.h"
#include "GameplayEffectExtension.h"

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute %f %f"),Health.GetCurrentValue(),Health.GetBaseValue());
	float OldValue = Health.GetCurrentValue();
	float NewValue = FMath::Clamp(OldValue + Data.EvaluatedData.Magnitude, 0.0f, Health.GetBaseValue());
	
	float Delta = Data.EvaluatedData.Magnitude;

	OnHealthChanged.Broadcast(Delta, NewValue);	
}

void UHealthAttributeSet::InitializeAttributes(float InHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("InitializeAttributes"));
	Health.SetBaseValue(InHealth);
	Health.SetCurrentValue(InHealth);
}
