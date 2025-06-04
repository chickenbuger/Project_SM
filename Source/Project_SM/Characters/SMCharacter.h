// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SMCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputMappingContext;

class UWidgetComponent;
class USMPlayerInfo;

UCLASS()
class PROJECT_SM_API ASMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASMCharacter();

public:
	FORCEINLINE USpringArmComponent* GetSpringArm() const	{ return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const			{ return Camera; }
	FORCEINLINE FString GetPlayerName() const				{ return PlayerName; }

public:
	void Init();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToLocation(const FVector& TargetLocation);

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PlayerInfoWidgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> PlayerInfoWidgetComponent;

	UPROPERTY()
	TObjectPtr<USMPlayerInfo> PlayerInfoWidget;

	UPROPERTY(Category = User, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString PlayerName;

private:
	UFUNCTION()
	void OnHealthChanged(float EffectMagnitude, float NewValue);
};
