// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SMCharacter.h"				// 자신 헤더 
#include "Controller/AI/SMAIController.h"		// Ai 컨트롤러

#include "GameFramework/SpringArmComponent.h"	// SpringArm
#include "Camera/CameraComponent.h"				// Camera

// Sets default values
ASMCharacter::ASMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 카메라 세팅
	{
		SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
		SpringArm->SetupAttachment(RootComponent);

		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(SpringArm);

		SpringArm->SetRelativeRotation(FRotator(300.0f, 0.0f, 0.0f));
		SpringArm->TargetArmLength = 1000.0f;

		SpringArm->bInheritYaw = false;
	}

	// Ai 컨트롤러 설정
	{
		AutoPossessAI = EAutoPossessAI::Disabled;
		AIControllerClass = nullptr;
	}
}
	
// Called when the game starts or when spawned
void ASMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASMCharacter::MoveToLocation(const FVector& TargetLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("Move Pos : %s"), *TargetLocation.ToString());
	ASMAIController* AiControl = Cast<ASMAIController>(GetController());
	if (AiControl)
	{
		AiControl->MoveToLocation(TargetLocation);
	}
}