// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_PlayerController.h"

#include "P00_ActionHandlerComponent.h"
#include "P00_InputComponent.h"
#include "P00_PlayerCharacter.h"
#include "WP00_PlayerHUD.h"
#include "Kismet/GameplayStatics.h"

AP00_PlayerController::AP00_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsRepossessed = false;
	SetupComponents();
}

void AP00_PlayerController::SetGameInput(const bool Value)
{
	Value ? SetInputGameOnly() : SetInputUIOnly();
}

void AP00_PlayerController::SetupComponents()
{
	if (!InputHandlerComponent)
	{
		InputHandlerComponent = CreateDefaultSubobject<UP00_InputComponent>(TEXT("Input Component"));
	}
}

void AP00_PlayerController::SetInputGameOnly()
{
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(false);
	
	SetIgnoreMoveInput(false);
	SetShowMouseCursor(false);
	SetInputMode(InputMode);
}

void AP00_PlayerController::SetInputUIOnly()
{
	FInputModeUIOnly InputMode;

	SetIgnoreMoveInput(true);
	SetShowMouseCursor(true);
	SetInputMode(InputMode);
}

void AP00_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!bIsRepossessed && ensure(InputHandlerComponent))
	{
		InputHandlerComponent -> InitInput(this);
	}

	if (!PlayerHUDPtr)
	{
		if (ensureMsgf(PlayerHUDClass, TEXT("%s::OnPossess: PlayerHUDClass is NUll"), *GetNameSafe(this)))
		{
			PlayerHUDPtr = CreateWidget<UWP00_PlayerHUD>(this, PlayerHUDClass);
			PlayerHUDPtr -> AddToViewport();
		}
	}

	if (AP00_PlayerCharacter* PlayerCharacter = Cast<AP00_PlayerCharacter>(InPawn))
	{
		PlayerCharacter -> InitInput(this);

		if (PlayerHUDPtr)
		{
			PlayerCharacter -> SpawnLightActor(PlayerHUDPtr -> GetLightProgressBar());
			PlayerCharacter -> SetKeyHolder(PlayerHUDPtr -> GetKeyHolder());
			PlayerCharacter -> SetDrainLightWidget(PlayerHUDPtr -> GetDebuffWidget());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AP00_PlayerController::BeginPlay: PlayerHUDPtr is NULL"));
		}
	}
	
	if (bIsRepossessed)
	{
		if (AP00_PlayerCharacter* PlayerCharacter = Cast<AP00_PlayerCharacter>(GetPawn()))
		{
			PlayerCharacter -> GetActionComponent() -> AddKeyTags(KeyTags);
			bIsRepossessed = false;
		}
	}
}

void AP00_PlayerController::OnUnPossess()
{
	bIsRepossessed = true;
	
	if (AP00_PlayerCharacter* PlayerCharacter = Cast<AP00_PlayerCharacter>(GetPawn()))
	{
		PlayerCharacter -> RestLightTimers();

		if (UP00_ActionHandlerComponent* ActionHandlerComponent = PlayerCharacter -> GetActionComponent())
		{
			KeyTags.AppendTags(ActionHandlerComponent -> GetKeyTags());
		}
	}
	
	Super::OnUnPossess();
}

void AP00_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputUIOnly();
	
	if (ensureMsgf(HelpWindowClass, TEXT("%s::OnPossess: HelpWindowClass is NUll"), *GetNameSafe(this)))
	{
		HelpWindowPtr = CreateWidget<UUserWidget>(this, HelpWindowClass);
		HelpWindowPtr -> AddToViewport();
		UGameplayStatics::SetGamePaused(this, true);
	}
}
