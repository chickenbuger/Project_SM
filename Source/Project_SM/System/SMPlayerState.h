// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASPlayerState.h"
#include "SMPlayerState.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_SM_API ASMPlayerState : public AGASPlayerState
{
	GENERATED_BODY()
	
public:
	ASMPlayerState();

public:
	virtual void Init() override;

public:
	FORCEINLINE const FString GetUserName() const { return UserName; }

private:
	UPROPERTY(Category = User, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString UserName;
};
