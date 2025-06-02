// Fill out your copyright notice in the Description page of Project Settings.


#include "SMGameMode.h"

ASMGameMode::ASMGameMode()
{
	// ĳ���� ���� ����
	DefaultPawnClass = nullptr;
}

void ASMGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("ASMGameMode HandleStartingNewPlayer_Implementation"));

	// ���� ��ġ ����
	FVector SpawnLocation	= FVector(0.0f, 0.0f, 0.0f);
	FRotator SpawnRotation	= FRotator::ZeroRotator;

	// ĳ���� ���� �� Possess
	if (PlayerPawnClass && NewPlayer)
	{
		APawn* NewPawn = GetWorld()->SpawnActor<APawn>(PlayerPawnClass, SpawnLocation, SpawnRotation);
		if (NewPawn)
		{
			NewPlayer->Possess(NewPawn);
		}
	}
}