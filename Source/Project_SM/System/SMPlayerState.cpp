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

	HealthAttributeSet = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("HealthAttributeSet"));
}

void ASMPlayerState::Init()
{
	if (HealthAttributeSet)
	{
		HealthAttributeSet->OnHealthChanged.AddDynamic(this, &ASMPlayerState::HandleHealthChanged);
	}

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetNumericAttributeBase(UHealthAttributeSet::GetHealthAttribute(), InitialHealth);
	}

}

UAbilitySystemComponent* ASMPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASMPlayerState::HandleHealthChanged(float Magnitude, float NewHealth)
{
	if (NewHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ü���� 0 ����"));
	}
}
