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
	// �÷��̾ �����Ǹ� ȣ��
	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	// �÷��̾� Class
	UPROPERTY(EditDefaultsOnly, Category = "Player", meta=(AllowPrivateAccess = "true"))
	TSubclassOf<APawn> PlayerPawnClass;
};
