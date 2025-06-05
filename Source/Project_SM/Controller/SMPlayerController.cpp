// Fill out your copyright notice in the Description page of Project Settings.

#include "SMPlayerController.h"						    // �ڽ� ���

#include "Characters/SMCharacter.h"                     // ĳ����
#include "Controller/AI/SMAIController.h"               // Ai��Ʈ�ѷ�

#include "EnhancedInputComponent.h"						// Enhanced Input ���ε���
#include "InputAction.h"								// Input Action Ÿ��
#include "InputActionValue.h"							// InputActionValue Ÿ��

ASMPlayerController::ASMPlayerController()
{
    // ���콺 ����
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
    // Ŀ�� �Ʒ� ��ġ�� Ȯ��
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
        // ���ε�
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
    // ASMCharacter Class ���� Ȯ��
    if (Cast<ASMCharacter>(InPawn))
    {
        // ĳ���� ������ ����(Unpossess ����)
        PlayerCharacter = Cast<ASMCharacter>(InPawn);

        SetupCharacterInput();

        // ���������� Ai controller�� �����Ǹ� Controller ��ü
        ASMAIController* AiControl = GetWorld()->SpawnActor<ASMAIController>();
        if (AiControl)
        {
            // ī�޶� �ڵ� ��ȯ ����
            this->bAutoManageActiveCameraTarget = false;

            // ���� Controller ���� ����
            OnUnPossess();

            // Ai Controller ����
            AiControl->Possess(PlayerCharacter);

            // ĳ������ ī�޶� ���󰡵��� ����
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
    // Input �ʱ�ȭ
    if (PlayerCharacter)
    {
        PlayerCharacter->Init();
    }
}
