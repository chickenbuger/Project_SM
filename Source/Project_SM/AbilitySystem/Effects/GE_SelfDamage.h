// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GE_SelfDamage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SM_API UGE_SelfDamage : public UGameplayEffect
{
	GENERATED_BODY()
	
public:
	UGE_SelfDamage();

	virtual FGameplayTagContainer BP_GetOwnedGameplayTags() const override;
};
