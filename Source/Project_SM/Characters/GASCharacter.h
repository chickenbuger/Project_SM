// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GASCharacter.generated.h"

UCLASS()
class PROJECT_SM_API AGASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASCharacter();

public:
	void TestClick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
