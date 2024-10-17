// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P00_BaseCharacter.h"
#include "P00_PlayerCharacter.generated.h"

class AP00_PlayerController;
class UCameraComponent;
class USpringArmComponent;

struct FInputActionValue;

UCLASS()
class PROTOTYPE_00_API AP00_PlayerCharacter : public AP00_BaseCharacter
{
	GENERATED_BODY()

public:
	AP00_PlayerCharacter();
	void InitInput(AP00_PlayerController* PlayerController);

private:
	void SetupCameraComponent();
	
private:
	void ExecutePlayerMove(const FInputActionValue& InputActionValue);
	void ExecutePlayerTurn(const FInputActionValue& InputActionValue);
	void ExecutePlayerJump(const FInputActionValue& InputActionValue);
	void ExecutePlayerFire(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
};
