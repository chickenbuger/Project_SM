// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAttributeSet.h"
#include "GameplayEffectExtension.h"

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute C %f, M %f"), Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// 현재 HP 변화
	}
	else if(Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		// Max HP 변화
	}

	OnHealthChanged.Broadcast(Data.EvaluatedData.Magnitude,Health.GetCurrentValue());
}
