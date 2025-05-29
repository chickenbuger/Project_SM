// Fill out your copyright notice in the Description page of Project Settings.

#include "SMPlayerController.h"						// 자신 헤더
#include "EnhancedInputComponent.h"                 // Enhanced Input 바인딩용
#include "EnhancedInputSubsystems.h"                // Input Mapping Context 등록용
#include "InputMappingContext.h"                    // Mapping Context 타입
#include "InputAction.h"                            // Input Action 타입
#include "InputActionValue.h"                       // InputActionValue 타입

#include "Characters/SMCharacter.h"                 // 캐릭터
#include "Controller/AI/SMAIController.h"           // Ai컨트롤러

ASMPlayerController::ASMPlayerController()
{
    // 마우스 세팅
    {
        bShowMouseCursor = true;
        bEnableClickEvents = true;
        bEnableMouseOverEvents = true;

        DefaultMouseCursor = EMouseCursor::Default;
    }
}

void ASMPlayerController::SetPlayerCharacter(ASMCharacter* InCharacter)
{
    PlayerCharacter = InCharacter;
}

void ASMPlayerController::BeginPlay()
{
	Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(this))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ASMPlayerController::SetupInputComponent()
{
    InputComponent = NewObject<UEnhancedInputComponent>(this, TEXT("EnhancedInputComponent"));
    InputComponent->RegisterComponent();

    PushInputComponent(InputComponent);

    if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
    {
        Input->BindAction(MouseClickAction, ETriggerEvent::Started, this, &ASMPlayerController::OnMouseClick);
    }
}

void ASMPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (InPawn)
    {
        SwapControllerToAIController(InPawn);
    }
}

void ASMPlayerController::OnUnPossess()
{
    Super::OnUnPossess();
}

void ASMPlayerController::OnMouseClick(const FInputActionValue& Value)
{
    FHitResult Hit;
    // 커서 아래 위치를 확인
    if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
    {
        if (PlayerCharacter)
        {
            //이동 명령 전달
            PlayerCharacter->MoveToLocation(Hit.ImpactPoint);
        }
    }
}

void ASMPlayerController::SwapControllerToAIController(APawn* InPawn)
{
    // ASMCharacter Class 인지 확인
    if (Cast<ASMCharacter>(InPawn))
    {
        // 캐릭터 정보를 저장(Unpossess 이전)
        PlayerCharacter = Cast<ASMCharacter>(InPawn);

        // 성공적으로 Ai controller가 생성되면 Controller 교체
        ASMAIController* AiControl = GetWorld()->SpawnActor<ASMAIController>();
        if (AiControl)
        {
            // 카메라 자동 변환 해제
            this->bAutoManageActiveCameraTarget = false;

            // 기존 Controller 연결 해제
            OnUnPossess();

            // Ai Controller 연결
            AiControl->Possess(PlayerCharacter);

            // 캐릭터의 카메라를 따라가도록 연결
            SetViewTargetWithBlend(PlayerCharacter, 0.0f);
        }
    }
}
