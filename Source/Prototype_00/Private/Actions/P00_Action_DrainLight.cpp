// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_Action_DrainLight.h"
#include "P00_ActionHandlerComponent.h"
#include "P00_AICharacter.h"
#include "P00_PlayerCharacter.h"

void UP00_Action_DrainLight::ApplyPeriodicEffect(AActor* Instigator)
{
	if (UP00_ActionHandlerComponent* AC = GetOwningComponent())
	{
		if (AP00_PlayerCharacter* Player = Cast<AP00_PlayerCharacter>(AC -> GetOwner()))
		{
			if (Player -> GetIsProtected())
			{
				return;
			}
			
			Player -> ReduceLight(DrainAmount, Instigator);

			if (AP00_AICharacter* AI = Cast<AP00_AICharacter>(Instigator))
			{
				AI -> AddStoredLight(DrainAmount);
			}
		}
	}
}

void UP00_Action_DrainLight::StopAction(AActor* Instigator)
{
	Super::StopAction(Instigator);

	if (UP00_ActionHandlerComponent* AC = GetOwningComponent())
	{
		if (AP00_PlayerCharacter* Player = Cast<AP00_PlayerCharacter>(AC -> GetOwner()))
		{
			Player -> SetDrainLightWidgetVisibility(false);
		}
	}
}
