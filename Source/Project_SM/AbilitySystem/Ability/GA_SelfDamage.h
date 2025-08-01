// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_SelfDamage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SM_API UGA_SelfDamage : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_SelfDamage();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;;
};
