// Fill out your copyright notice in the Description page of Project Settings.


#include "SMCharacter.h"								// 자신 헤더 
#include "Controller/AI/SMAIController.h"				// Ai 컨트롤러
#include "GameFramework/CharacterMovementComponent.h"	// 캐릭터 움직임

#include "EnhancedInputSubsystems.h"					// Input Mapping Context 등록용
#include "InputMappingContext.h"						// Mapping Context 타입

#include "GameFramework/SpringArmComponent.h"			// SpringArm
#include "Camera/CameraComponent.h"						// Camera

#include "AbilitySystemComponent.h"						// GAS
#include "System/SMPlayerState.h"						// PlayerState

#include "Widgets/Player/SMPlayerInfo.h"				// Player Info
#include "Components/WidgetComponent.h"					// Widget Components

#include "AbilitySystem/Attributes/HealthAttributeSet.h"

// Sets default values
ASMCharacter::ASMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Player Widget 세팅
	{
		PlayerInfoWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerInfoWidget"));
		PlayerInfoWidgetComponent->SetupAttachment(GetMesh());

		PlayerInfoWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		PlayerInfoWidgetComponent->SetDrawSize(FVector2D(500.0f, 500.0f));
		PlayerInfoWidgetComponent->SetDrawAtDesiredSize(true);

		PlayerInfoWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		PlayerInfoWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	}

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

	// 캐릭터 회전
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f,720.0f,0.0f);

		bUseControllerRotationYaw = false;
	}

	// Ai 컨트롤러 설정
	{
		AutoPossessAI = EAutoPossessAI::Disabled;
		AIControllerClass = nullptr;
	}

	PlayerName = "TestName";
}
	
// Called when the game starts or when spawned
void ASMCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Init GAS
	{
		ASMPlayerState* PS = GetPlayerState<ASMPlayerState>();
		if (PS)
		{
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			if (ASC)
			{
				//Owner(소유자)  Avatar(실행자)	
				ASC->InitAbilityActorInfo(PS, this);

				PS->Init();
			}
		}
	}
}

void ASMCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ASMPlayerState* PS = GetPlayerState<ASMPlayerState>())
	{
		if (UHealthAttributeSet* HealthSet = PS->HealthAttributeSet)
		{
			HealthSet->OnHealthChanged.RemoveDynamic(this, &ASMCharacter::OnHealthChanged);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void ASMCharacter::OnHealthChanged(float EffectMagnitude, float NewValue)
{
	if (PlayerInfoWidget)
	{
		ASMPlayerState* PS = GetPlayerState<ASMPlayerState>();
		if (!PS)
		{
			return;
		}
		const float BaseHP = PS->HealthAttributeSet->Health.GetBaseValue();

		PlayerInfoWidget->UpdateInfo(BaseHP, NewValue);
	}
}

void ASMCharacter::Init()
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
				// 초기 체력 설정
				PlayerInfoWidget->SetHealthPercent(1.0f);
				// 이름 설정
				if (APlayerState* PS = GetPlayerState())
				{
					// PlayerState로 옮길 예정
					PlayerInfoWidget->SetPlayerName(PlayerName);
				}
			}
		}
	}

	// Attribute Bind
	{
		if (ASMPlayerState* PS = GetPlayerState<ASMPlayerState>())
		{
			// HP
			if (UHealthAttributeSet* HealthSet = PS->HealthAttributeSet)
			{
				HealthSet->OnHealthChanged.AddUniqueDynamic(this, &ASMCharacter::OnHealthChanged);
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