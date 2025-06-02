// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGameMode.h"

ASMGameMode::ASMGameMode()
{
	// 캐릭터 생성 방지
	DefaultPawnClass = nullptr;
}

void ASMGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("ASMGameMode HandleStartingNewPlayer_Implementation"));

	// 스폰 위치 지정
	FVector SpawnLocation	= FVector(0.0f, 0.0f, 0.0f);
	FRotator SpawnRotation	= FRotator::ZeroRotator;

	// 캐릭터 생성 및 Possess
	if (PlayerPawnClass && NewPlayer)
	{
		APawn* NewPawn = GetWorld()->SpawnActor<APawn>(PlayerPawnClass, SpawnLocation, SpawnRotation);
		if (NewPawn)
		{
			NewPlayer->Possess(NewPawn);
		}
	}
}