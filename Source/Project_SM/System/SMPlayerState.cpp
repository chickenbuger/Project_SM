// Fill out your copyright notice in the Description page of Project Settings.


#include "SMPlayerState.h"

#include "Characters/SMCharacter.h"							// ĳ����

#include "AbilitySystem/Attributes/HealthAttributeSet.h"	// Hp
#include "AbilitySystemComponent.h"							// GAS

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

	UserName = "TestJS";
}

void ASMPlayerState::Init()
{
	if (HealthAttributeSet)
	{
		HealthAttributeSet->OnHealthChanged.AddDynamic(this, &ASMPlayerState::HandleHealthChanged);
	}
	
	// HealthAttributeSet�� �ʱ�ȭ (Init)
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
		UE_LOG(LogTemp, Warning, TEXT("ü���� 0 �̸�"));
		return;
	}

	if (!OwningPlayerCharacter) return;

	const float MaxHP = HealthAttributeSet->MaxHealth.GetCurrentValue();

	OwningPlayerCharacter->OnHealthChanged(MaxHP, NewHealth);
}
