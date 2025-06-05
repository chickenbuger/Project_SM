// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_SelfDamage.h"
#include "AbilitySystem/Attributes/HealthAttributeSet.h"

UGE_SelfDamage::UGE_SelfDamage()
{
    // 즉각 반영
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo Modifier;

    // 조절 대상
    Modifier.Attribute = UHealthAttributeSet::GetHealthAttribute();
    // 덧셈
    Modifier.ModifierOp = EGameplayModOp::Additive;
    // 변경점 (-10만큼 변경)
    Modifier.ModifierMagnitude = FScalableFloat(-10.0f); // -10 데미지

    // Effect에 추가 (여러 개 가능)
    Modifiers.Add(Modifier);
}

FGameplayTagContainer UGE_SelfDamage::BP_GetOwnedGameplayTags() const
{
    return FGameplayTagContainer();
}
