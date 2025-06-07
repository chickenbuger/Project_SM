// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GASPlayerState.h"

#include "AbilitySystem/Attributes/HealthAttributeSet.h"	// Hp
#include "AbilitySystemComponent.h"							// GAS

#include "Characters/SMCharacter.h"							// 캐릭터

AGASPlayerState::AGASPlayerState()
{
	// GAS 세팅
	{
		AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	}

	// SubObject 생성
	{
		HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttributeSet"));
	}
}

UAbilitySystemComponent* AGASPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASPlayerState::Init()
{
	if (HealthAttributeSet)
	{
		HealthAttributeSet->OnHealthChanged.AddDynamic(this, &AGASPlayerState::HandleHealthChanged);
	}

	// HealthAttributeSet의 초기화 (Init)
	if (AbilitySystemComponent && OwningPlayerCharacter)
	{
		if (!OwningPlayerCharacter->InitAttributeEffect) return;

		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(OwningPlayerCharacter->InitAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

const ASMCharacter* AGASPlayerState::GetOwningPlayerCharacter() const
{
	return OwningPlayerCharacter;
}

void AGASPlayerState::SetOwningPlayerCharacter(ACharacter* InOwningCharacter)
{
	OwningPlayerCharacter = Cast<ASMCharacter>(InOwningCharacter);
}

void AGASPlayerState::HandleHealthChanged(float Magnitude, float NewHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("HandleHealthChanged %f, %f"), Magnitude, NewHealth);
	if (NewHealth < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health < 0"));
		return;
	}

	if (!OwningPlayerCharacter) return;

	const float MaxHP = HealthAttributeSet->MaxHealth.GetCurrentValue();

	OwningPlayerCharacter->OnHealthChanged(MaxHP, NewHealth);
}