// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "P00_PlayerController.h"
#include "P00_StringLibrarary.h"

UP00_InputComponent::UP00_InputComponent(): PlayerControllerPtr(nullptr), InputConfig(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UP00_InputComponent::InitInput(AP00_PlayerController* PlayerController)
{
	if (ensure(PlayerController))
	{
		PlayerControllerPtr = PlayerController;
		InputConfig = LoadObject<UP00_InputConfig>(this, *FPathLibrary::InputConfigPath);

		if (InputConfig)
		{
			if (InputConfig -> SetupInputActions())
			{
				if (AddMappingContext(InputConfig))
				{
					if (!InitEnhancedInputComponent(InputConfig))
					{
						UE_LOG(LogTemp, Error, TEXT("%s/%s::OnRegister: Failed to Init Enhanced Input Component"), *GetNameSafe(GetOwner()), *GetNameSafe(this))
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("%s/%s::OnRegister: Failed to Add Mapping Context"), *GetNameSafe(GetOwner()), *GetNameSafe(this))
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("%s/%s::OnRegister: Failed to Setup Input Actions in Config"), *GetNameSafe(GetOwner()), *GetNameSafe(this))
			}
		}
	}
}

bool UP00_InputComponent::AddMappingContext(const UP00_InputConfig* Config)
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControllerPtr -> GetLocalPlayer());

	if (!ensure(Subsystem))
	{
		UE_LOG(LogTemp, Error, TEXT("%s/%s::AddMappingContext: PlayerSubsystem is NULL"), *GetNameSafe(GetOwner()), *GetNameSafe(this));
		return false;
	}

	if (!ensureMsgf(Config -> IMC_BaseContext.IsValid(), TEXT("%s/s::AddMappingContext: MappingContext is NULL"), *GetNameSafe(GetOwner()), *GetNameSafe(this)))
	{
		return false;
	}
		
	Subsystem -> AddMappingContext(Config -> IMC_BaseContext.Get(), Config -> ContextPriority);
	return true;
}

bool UP00_InputComponent::InitEnhancedInputComponent(const UP00_InputConfig* Config)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerControllerPtr -> InputComponent))
	{
		EnhancedInputComponent -> BindAction(Config -> IA_Move.Get(), ETriggerEvent::Triggered, this, &ThisClass::HandleMove);
		EnhancedInputComponent -> BindAction(Config -> IA_Turn.Get(), ETriggerEvent::Triggered, this, &ThisClass::HandleTurn);
		EnhancedInputComponent -> BindAction(Config -> IA_Jump.Get(), ETriggerEvent::Started, this, &ThisClass::HandleJump);
		EnhancedInputComponent -> BindAction(Config -> IA_Fire.Get(), ETriggerEvent::Started, this, &ThisClass::HandleFire);
		
		return true;
	}

	UE_LOG(LogTemp, Error, TEXT("%s/%s::InitEnhancedInputComponent: EnhancedInputComponent is NULL"), *GetNameSafe(GetOwner()), *GetNameSafe(this));
	return false;
}

void UP00_InputComponent::HandleMove(const FInputActionValue& InputActionValue)
{
	if (PlayerControllerPtr)
	{
		PlayerControllerPtr -> OnCharacterMove.Broadcast(InputActionValue);
	}
}

void UP00_InputComponent::HandleTurn(const FInputActionValue& InputActionValue)
{
	if (PlayerControllerPtr)
	{
		PlayerControllerPtr -> OnCharacterTurn.Broadcast(InputActionValue);
	}
}

void UP00_InputComponent::HandleJump(const FInputActionValue& InputActionValue)
{
	if (PlayerControllerPtr)
	{
		PlayerControllerPtr -> OnCharacterJump.Broadcast(InputActionValue);
	}
}

void UP00_InputComponent::HandleFire(const FInputActionValue& InputActionValue)
{
	if (PlayerControllerPtr)
	{
		PlayerControllerPtr -> OnCharacterFire.Broadcast(InputActionValue);
	}
}
