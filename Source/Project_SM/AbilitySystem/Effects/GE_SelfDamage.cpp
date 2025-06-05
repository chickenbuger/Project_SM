// Fill out your copyright notice in the Description page of Project Settings.


#include "GE_SelfDamage.h"
#include "AbilitySystem/Attributes/HealthAttributeSet.h"

UGE_SelfDamage::UGE_SelfDamage()
{
    // �ﰢ �ݿ�
    DurationPolicy = EGameplayEffectDurationType::Instant;

    FGameplayModifierInfo Modifier;

    // ���� ���
    Modifier.Attribute = UHealthAttributeSet::GetHealthAttribute();
    // ����
    Modifier.ModifierOp = EGameplayModOp::Additive;
    // ������ (-10��ŭ ����)
    Modifier.ModifierMagnitude = FScalableFloat(-10.0f); // -10 ������

    // Effect�� �߰� (���� �� ����)
    Modifiers.Add(Modifier);
}

FGameplayTagContainer UGE_SelfDamage::BP_GetOwnedGameplayTags() const
{
    return FGameplayTagContainer();
}
