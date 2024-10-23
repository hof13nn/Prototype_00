// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WP00_ProgressBar.h"
#include "UObject/Object.h"
#include "WP00_LightProgressBar.generated.h"

UCLASS()
class PROTOTYPE_00_API UWP00_LightProgressBar : public UWP00_ProgressBar
{
	GENERATED_BODY()

public:
	void SetBarCooldownTimer(const float& Duration);
	void SetBarCooldownValue(const float& Value);
	
private:
	void UpdateLightDecreaseCooldownBarValue(const float& Value);
	void StopUpdateLightDecreaseCooldownBarValue(const float& Duration);
	
protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* LightDecreaseCooldownBar;
	UPROPERTY(EditDefaultsOnly, Category= "Timer")
	float Rate;
	FTimerHandle Bar_TimerHandle;
	FTimerHandle BarUpdate_TimerHandle;
};