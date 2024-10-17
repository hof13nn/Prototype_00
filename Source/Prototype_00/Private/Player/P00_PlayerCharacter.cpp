// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_PlayerCharacter.h"
#include "InputActionValue.h"
#include "P00_PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AP00_PlayerCharacter::AP00_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SetupCameraComponent();
}

void AP00_PlayerCharacter::InitInput(AP00_PlayerController* PlayerController)
{
	PlayerController -> OnCharacterMove.AddUObject(this, &ThisClass::ExecutePlayerMove);
	PlayerController -> OnCharacterTurn.AddUObject(this, &ThisClass::ExecutePlayerTurn);
	PlayerController -> OnCharacterJump.AddUObject(this, &ThisClass::ExecutePlayerJump);
	PlayerController -> OnCharacterFire.AddUObject(this, &ThisClass::ExecutePlayerFire);
}

void AP00_PlayerCharacter::SetupCameraComponent()
{
	if (!SpringArmComponent)
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));

		if (ensure(SpringArmComponent))
		{
			SpringArmComponent -> TargetArmLength = 500.f;
			SpringArmComponent -> bUsePawnControlRotation = true;
			SpringArmComponent -> SetupAttachment(RootComponent);
			
			if (!CameraComponent)
			{
				CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));

				if (ensure(CameraComponent))
				{
					CameraComponent -> SetupAttachment(SpringArmComponent);
				}
			}
		}
	}
}

void AP00_PlayerCharacter::ExecutePlayerMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);
		
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AP00_PlayerCharacter::ExecutePlayerTurn(const FInputActionValue& InputActionValue)
{
}

void AP00_PlayerCharacter::ExecutePlayerJump(const FInputActionValue& InputActionValue)
{
	Jump();
}

void AP00_PlayerCharacter::ExecutePlayerFire(const FInputActionValue& InputActionValue)
{
}
