// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SMCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveToLocation(const FVector& TargetLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;
};
