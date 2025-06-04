// Fill out your copyright notice in the Description page of Project Settings.


#include "SMHealthWidget.h"
#include "Components/ProgressBar.h"

void USMHealthWidget::SetHealthPercent(float NewPercent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(NewPercent);
	}
}

void USMHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
