// Fill out your copyright notice in the Description page of Project Settings.


#include "SMPlayerState.h"

#include "Characters/SMCharacter.h"							// 캐릭터

#include "AbilitySystem/Attributes/HealthAttributeSet.h"	// Hp
#include "AbilitySystemComponent.h"							// GAS

ASMPlayerState::ASMPlayerState()
{
	// GAS 세팅
	{
		AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	}
	
	// SubObject 생성
	{
		HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttributeSet"));
	}

	UserName = "TestJS";
}

void ASMPlayerState::Init()
{
	if (HealthAttributeSet)
	{
		HealthAttributeSet->OnHealthChanged.AddDynamic(this, &ASMPlayerState::HandleHealthChanged);
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

void ASMPlayerState::SetOwningPlayerCharacter(ASMCharacter* InOwningCharacter)
{
	OwningPlayerCharacter = InOwningCharacter;
}

UAbilitySystemComponent* ASMPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASMPlayerState::HandleHealthChanged(float Magnitude, float NewHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("HandleHealthChanged %f, %f"), Magnitude, NewHealth);
	if (NewHealth < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("체력이 0 미만"));
		return;
	}

	if (!OwningPlayerCharacter) return;

	const float MaxHP = HealthAttributeSet->MaxHealth.GetCurrentValue();

	OwningPlayerCharacter->OnHealthChanged(MaxHP, NewHealth);
}
