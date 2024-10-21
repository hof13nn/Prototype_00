// Fill out your copyright notice in the Description page of Project Settings.


#include "WP00_LightProgressBar.h"
#include "Components/ProgressBar.h"

void UWP00_LightProgressBar::SetBarCooldownTimer(const float& Duration)
{
	if (GetWorld() -> GetTimerManager().TimerExists(Bar_TimerHandle))
	{
		GetWorld() -> GetTimerManager().ClearTimer(Bar_TimerHandle);
	}
	if (GetWorld() -> GetTimerManager().TimerExists(BarUpdate_TimerHandle))
	{
		GetWorld() -> GetTimerManager().ClearTimer(BarUpdate_TimerHandle);
	}
	
	LightDecreaseCooldownBar -> SetPercent(1.f);
	GetWorld() -> GetTimerManager().SetTimer(Bar_TimerHandle, [&, Duration]{ StopUpdateLightDecreaseCooldownBarValue( Rate / Duration ); }, Duration, false);
	GetWorld() -> GetTimerManager().SetTimer(BarUpdate_TimerHandle, [&, Duration]{ UpdateLightDecreaseCooldownBarValue( Rate / Duration ); }, Rate, true);
}

void UWP00_LightProgressBar::UpdateLightDecreaseCooldownBarValue(const float& Value)
{
	const float CurrentPercent = LightDecreaseCooldownBar -> GetPercent();
	LightDecreaseCooldownBar -> SetPercent(CurrentPercent - Value);
}

void UWP00_LightProgressBar::StopUpdateLightDecreaseCooldownBarValue(const float& Duration)
{
	if (GetWorld() -> GetTimerManager().GetTimerRemaining(BarUpdate_TimerHandle) < KINDA_SMALL_NUMBER)
	{
		LightDecreaseCooldownBar -> SetPercent(Duration);
	}

	GetWorld() -> GetTimerManager().ClearTimer(Bar_TimerHandle);
	GetWorld() -> GetTimerManager().ClearTimer(BarUpdate_TimerHandle);
}
