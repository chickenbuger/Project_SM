// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_SelfDamage.h"
#include "AbilitySystem/Effects/GE_SelfDamage.h"    // Effects
#include "AbilitySystemComponent.h"                 // ASC

UGA_SelfDamage::UGA_SelfDamage()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_SelfDamage::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
    // Ability가 발동될 수 있는 조건 체크
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

    // ASC 존재 확인
    if (ActorInfo->AbilitySystemComponent.IsValid())
    {
        FGameplayEffectSpecHandle DamageSpecHandle = ActorInfo->AbilitySystemComponent->MakeOutgoingSpec(UGE_SelfDamage::StaticClass(), 1.f, ActorInfo->AbilitySystemComponent->MakeEffectContext());

        if (DamageSpecHandle.IsValid())
        {
            ActorInfo->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
        }
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
