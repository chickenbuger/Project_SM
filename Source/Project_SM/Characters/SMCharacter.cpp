// Fill out your copyright notice in the Description page of Project Settings.


#include "SMCharacter.h"								// �ڽ� ��� 
#include "Controller/AI/SMAIController.h"				// Ai ��Ʈ�ѷ�
#include "GameFramework/CharacterMovementComponent.h"	// ĳ���� ������

#include "EnhancedInputSubsystems.h"					// Input Mapping Context ��Ͽ�
#include "InputMappingContext.h"						// Mapping Context Ÿ��

#include "GameFramework/SpringArmComponent.h"			// SpringArm
#include "Camera/CameraComponent.h"						// Camera

#include "Widgets/Player/SMPlayerInfo.h"				// Player Info
#include "Components/WidgetComponent.h"					// Widget Components	

#include "System/SMPlayerState.h"						// PlayerState

// Sets default values
ASMCharacter::ASMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Player Widget ����
	{
		PlayerInfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerInfoWidget"));
		PlayerInfoWidgetComponent->SetupAttachment(GetMesh());

		PlayerInfoWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		PlayerInfoWidgetComponent->SetDrawSize(FVector2D(500.0f, 500.0f));
		PlayerInfoWidgetComponent->SetDrawAtDesiredSize(true);

		PlayerInfoWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		PlayerInfoWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	}

	// ī�޶� ����
	{
		SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
		SpringArm->SetupAttachment(RootComponent);

		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(SpringArm);

		SpringArm->SetRelativeRotation(FRotator(300.0f, 0.0f, 0.0f));
		SpringArm->TargetArmLength = 1000.0f;

		SpringArm->bInheritYaw = false;
	}

	// ĳ���� ȸ��
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f,720.0f,0.0f);

		bUseControllerRotationYaw = false;
	}

	// Ai ��Ʈ�ѷ� ����
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

void ASMCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASMCharacter::OnHealthChanged(const float InMaxHealth, const float InNewHealth)
{
	PlayerInfoWidget->UpdateInfo(InMaxHealth, InNewHealth);
}

void ASMCharacter::InputInit()
{
	// PlayerController Input Mappings
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void ASMCharacter::LateInit()
{
	// Widget Bind
	{
		PlayerInfoWidgetComponent->SetWidgetClass(PlayerInfoWidgetClass);
		PlayerInfoWidgetComponent->InitWidget();

		UUserWidget* Widget = PlayerInfoWidgetComponent->GetUserWidgetObject();
		if(Widget)
		{
			PlayerInfoWidget = Cast<USMPlayerInfo>(Widget);
			if (PlayerInfoWidget)
			{
				// �ʱ� ü�� ����
				PlayerInfoWidget->SetHealthPercent(1.0f);
				// �̸� ����
				if (ASMPlayerState* PS = GetPlayerState<ASMPlayerState>())
				{
					// PlayerState�� �ű� ����
					PlayerInfoWidget->SetPlayerName(PS->GetUserName());
				}
			}
		}
	}
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
	ASMAIController* AiControl = Cast<ASMAIController>(GetController());
	if (AiControl)
	{
		AiControl->MoveToLocation(TargetLocation);
	}
}
