// Fill out your copyright notice in the Description page of Project Settings.

#include "SMPlayerController.h"						// �ڽ� ���
#include "EnhancedInputComponent.h"                 // Enhanced Input ���ε���
#include "EnhancedInputSubsystems.h"                // Input Mapping Context ��Ͽ�
#include "InputMappingContext.h"                    // Mapping Context Ÿ��
#include "InputAction.h"                            // Input Action Ÿ��
#include "InputActionValue.h"                       // InputActionValue Ÿ��

#include "Characters/SMCharacter.h"                 // ĳ����
#include "Controller/AI/SMAIController.h"           // Ai��Ʈ�ѷ�

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
    // Ŀ�� �Ʒ� ��ġ�� Ȯ��
    if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
    {
        if (PlayerCharacter)
        {
            //�̵� ��� ����
            PlayerCharacter->MoveToLocation(Hit.ImpactPoint);
        }
    }
}

void ASMPlayerController::SwapControllerToAIController(APawn* InPawn)
{
    // ASMCharacter Class ���� Ȯ��
    if (Cast<ASMCharacter>(InPawn))
    {
        // ĳ���� ������ ����(Unpossess ����)
        PlayerCharacter = Cast<ASMCharacter>(InPawn);

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
    }
}
