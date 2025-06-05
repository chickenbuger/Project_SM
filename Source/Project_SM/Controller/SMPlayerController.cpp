// Fill out your copyright notice in the Description page of Project Settings.

#include "SMPlayerController.h"						    // 자신 헤더

#include "Characters/SMCharacter.h"                     // 캐릭터
#include "Controller/AI/SMAIController.h"               // Ai컨트롤러

#include "EnhancedInputComponent.h"						// Enhanced Input 바인딩용
#include "InputAction.h"								// Input Action 타입
#include "InputActionValue.h"							// InputActionValue 타입

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
    UE_LOG(LogTemp, Log, TEXT("ASMPlayerController SetPlayerCharacter"));

    PlayerCharacter = InCharacter;
}

void ASMPlayerController::OnMouseClick(const FInputActionValue& Value)
{
    // 커서 아래 위치를 확인
    FHitResult Hit;
    if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
    {
        if (PlayerCharacter)
        {
            PlayerCharacter->MoveToLocation(Hit.ImpactPoint);
        }
    }
}

void ASMPlayerController::OnTestClick(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("OnTestClick"));

    if (PlayerCharacter)
    {
        ASMCharacter* PlayerActor = Cast<ASMCharacter>(PlayerCharacter);
        if (PlayerActor)
        {
            PlayerActor->TestClick();
        }
    }
}

void ASMPlayerController::BeginPlay()
{
	Super::BeginPlay();

    this->SetInputMode(FInputModeGameAndUI());
    EnableInput(this);
}

void ASMPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        // 바인딩
        EnhancedInput->BindAction(MouseClickAction, ETriggerEvent::Started, this, &ASMPlayerController::OnMouseClick);
        EnhancedInput->BindAction(TestClickAction, ETriggerEvent::Started, this, &ASMPlayerController::OnTestClick);
    }
}

void ASMPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    UE_LOG(LogTemp, Log, TEXT("Try ASMPlayerController OnPossess"));

    if (InPawn)
    {
        UE_LOG(LogTemp, Log, TEXT("ASMPlayerController OnPossess Succ"));

        SwapControllerToAIController(InPawn);
    }
}

void ASMPlayerController::OnUnPossess()
{
    Super::OnUnPossess();
}

void ASMPlayerController::SwapControllerToAIController(APawn* InPawn)
{
    // ASMCharacter Class 인지 확인
    if (Cast<ASMCharacter>(InPawn))
    {
        // 캐릭터 정보를 저장(Unpossess 이전)
        PlayerCharacter = Cast<ASMCharacter>(InPawn);

        SetupCharacterInput();

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
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("ASMPlayerController::SwapControllerToAIController Failed to find Ai Controller"));
        }
    }
}

void ASMPlayerController::SetupCharacterInput()
{
    // Input 초기화
    if (PlayerCharacter)
    {
        PlayerCharacter->Init();
    }
}
