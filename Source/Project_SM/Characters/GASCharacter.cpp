// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacter.h"

#include "AbilitySystemComponent.h"						// GAS
#include "System/SMPlayerState.h"						// PlayerState

#include "AbilitySystem/Attributes/HealthAttributeSet.h"
#include "AbilitySystem/Ability/GA_SelfDamage.h"

// Sets default values
AGASCharacter::AGASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Init GAS
	{
		ASMPlayerState* PS = GetPlayerState<ASMPlayerState>();
		if (PS)
		{
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			if (ASC)
			{
				ASC->GiveAbility(FGameplayAbilitySpec(UGA_SelfDamage::StaticClass(), 1, 0));

				// PlayerState에서 Character를 찾을 수 있도록 설정
				PS->SetOwningPlayerCharacter(this);
				PS->Init();

				//Owner(소유자)  Avatar(실행자)	
				ASC->InitAbilityActorInfo(PS, this);
			}
		}
	}
}

void AGASCharacter::TestClick()
{
	ASMPlayerState* SMPS = GetPlayerState<ASMPlayerState>();
	if (SMPS)
	{
		if (SMPS->GetAbilitySystemComponent())
		{
			FGameplayTagContainer TagContainer;
			TagContainer.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Ability.SelfDamage")));

			SMPS->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
		}
	}
}