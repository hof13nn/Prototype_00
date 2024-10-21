// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_Pickup_DoorKey.h"

#include "P00_PlayerCharacter.h"

void AP00_Pickup_DoorKey::StartInteract_Implementation(APawn* InstigatorPawn)
{
	Super::StartInteract_Implementation(InstigatorPawn);
	
	if (AP00_PlayerCharacter* PlayerCharacter = Cast<AP00_PlayerCharacter>(InstigatorPawn))
	{
		if (PlayerCharacter -> AddKey(KeyTag))
		{
			EndInteract_Implementation(InstigatorPawn);
		}
	}
}

void AP00_Pickup_DoorKey::EndInteract_Implementation(APawn* InstigatorPawn)
{
	Super::EndInteract_Implementation(InstigatorPawn);

	Destroy();
}