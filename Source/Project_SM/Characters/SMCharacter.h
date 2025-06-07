// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASCharacter.h"

#include "GameplayEffectTypes.h"						// Effects (FOnAttributeChangeData)

#include "SMCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputMappingContext;

class UWidgetComponent;
class USMPlayerInfo;

class UGameplayEffect;

UCLASS()
class PROJECT_SM_API ASMCharacter : public AGASCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASMCharacter();

public:
	FORCEINLINE USpringArmComponent* GetSpringArm() const	{ return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const			{ return Camera; }

public:
	// Init
	void InputInit();
	void LateInit();

	// Move Character
	void MoveToLocation(const FVector& TargetLocation);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Change Health Binding Func
	void OnHealthChanged(const float InMaxHealth, const float InNewHealth);

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PlayerInfoWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TSubclassOf<UGameplayEffect> InitAttributeEffect;
	
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
};
