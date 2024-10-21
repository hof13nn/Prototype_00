// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_ActionEffectBase.h"

#include "P00_ActionHandlerComponent.h"

void UP00_ActionEffectBase::StartAction(AActor* Instigator)
{
	Super::StartAction(Instigator);

	if (Duration > 0.f)
	{
		GetWorld() -> GetTimerManager().SetTimer(EffectDuration_TimerHandle, [&, Instigator]{ StopAction(Instigator); }, Duration, false);

		if (Rate > 0.f)
		{
			GetWorld() -> GetTimerManager().SetTimer(EffectRate_TimerHandle, [&, Instigator]{ ApplyPeriodicEffect(Instigator); }, Rate, true);
		}
	}
}

void UP00_ActionEffectBase::StopAction(AActor* Instigator)
{
	Super::StopAction(Instigator);

	if (GetWorld() -> GetTimerManager().GetTimerRemaining(EffectRate_TimerHandle) < KINDA_SMALL_NUMBER)
	{
		ApplyPeriodicEffect(Instigator);
	}
	
	Super::StopAction(Instigator);

	GetWorld() -> GetTimerManager().ClearTimer(EffectDuration_TimerHandle);
	GetWorld() -> GetTimerManager().ClearTimer(EffectRate_TimerHandle);

	UP00_ActionHandlerComponent* AC = GetOwningComponent();

	if (AC)
	{
		AC -> RemoveAction(this);
	}
}

void UP00_ActionEffectBase::ApplyPeriodicEffect(AActor* Instigator)
{
}
