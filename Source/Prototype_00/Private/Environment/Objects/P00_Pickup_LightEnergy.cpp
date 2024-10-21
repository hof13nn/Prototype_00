// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_Pickup_LightEnergy.h"
#include "P00_PlayerCharacter.h"

AP00_Pickup_LightEnergy::AP00_Pickup_LightEnergy()
{
	PrimaryActorTick.bCanEverTick = false;

	LightAmount = 0;
}

void AP00_Pickup_LightEnergy::StartInteract_Implementation(APawn* InstigatorPawn)
{
	Super::StartInteract_Implementation(InstigatorPawn);

	if (AP00_PlayerCharacter* PlayerCharacter = Cast<AP00_PlayerCharacter>(InstigatorPawn))
	{
		if (PlayerCharacter -> IncreaseLight(LightAmount))
		{
			EndInteract_Implementation(InstigatorPawn);
		}
	}
}

void AP00_Pickup_LightEnergy::EndInteract_Implementation(APawn* InstigatorPawn)
{
	Super::EndInteract_Implementation(InstigatorPawn);

	Destroy();
}

void AP00_Pickup_LightEnergy::SetLightAmount(const float& Value)
{
	LightAmount = Value;
}

