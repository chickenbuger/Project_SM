// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SMGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_SM_API ASMGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASMGameMode();

protected:
	// 플레이어가 생성되며 호출
	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	// 플레이어 Class
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<APawn> PlayerPawnClass;
};
