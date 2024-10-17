// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AP00_BaseCharacter::AP00_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement() -> bOrientRotationToMovement = true;
		bUseControllerRotationYaw = false;
	}
}

void AP00_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

