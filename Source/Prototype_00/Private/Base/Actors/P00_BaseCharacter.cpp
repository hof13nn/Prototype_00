// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_BaseCharacter.h"

#include "P00_ActionHandlerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AP00_BaseCharacter::AP00_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement() -> bOrientRotationToMovement = true;
		bUseControllerRotationYaw = false;
	}

	if (!ActionHandlerComponent)
	{
		ActionHandlerComponent = CreateDefaultSubobject<UP00_ActionHandlerComponent>(TEXT("Action Component"));

		if (ActionHandlerComponent)
		{
			AddOwnedComponent(ActionHandlerComponent);
		}
	}
}

UP00_ActionHandlerComponent* AP00_BaseCharacter::GetActionComponent() const
{
	return ActionHandlerComponent;
}

void AP00_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

