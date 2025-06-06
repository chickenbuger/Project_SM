// Fill out your copyright notice in the Description page of Project Settings.


#include "SMPlayerState.h"

#include "Characters/SMCharacter.h"							// ĳ����

#include "AbilitySystem/Attributes/HealthAttributeSet.h"	// Hp
#include "AbilitySystemComponent.h"							// Gas

ASMPlayerState::ASMPlayerState()
{
	// GAS ����
	{
		AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	}
	
	// SubObject ����
	{
		HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttributeSet"));
	}
}

void ASMPlayerState::Init()
{
	if (HealthAttributeSet)
	{
		HealthAttributeSet->InitializeAttributes(100.0f);
		HealthAttributeSet->OnHealthChanged.AddDynamic(this, &ASMPlayerState::HandleHealthChanged);
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
	UE_LOG(LogTemp, Warning, TEXT("HandleHealthChanged %f"), NewHealth);
	if (NewHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ü���� 0 ����"));
		return;
	}

	if (!OwningPlayerCharacter) return;

	const float Base = HealthAttributeSet->Health.GetBaseValue();

	OwningPlayerCharacter->OnHealthChanged(Base, NewHealth);
}
