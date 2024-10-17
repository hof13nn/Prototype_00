// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_PlayerController.h"
#include "P00_InputComponent.h"
#include "P00_PlayerCharacter.h"

AP00_PlayerController::AP00_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetupComponents();
}

void AP00_PlayerController::SetupComponents()
{
	if (!InputHandlerComponent)
	{
		InputHandlerComponent = CreateDefaultSubobject<UP00_InputComponent>(TEXT("Input Component"));
	}
}

void AP00_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (AP00_PlayerCharacter* PlayerCharacter = Cast<AP00_PlayerCharacter>(InPawn))
	{
		PlayerCharacter -> InitInput(this);
	}
}

void AP00_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(InputHandlerComponent))
	{
		InputHandlerComponent -> InitInput(this);
	}
}
