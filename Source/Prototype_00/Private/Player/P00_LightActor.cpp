// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_LightActor.h"
#include "WP00_LightProgressBar.h"
#include "Components/SpotLightComponent.h"

AP00_LightActor::AP00_LightActor()
{
	PrimaryActorTick.bCanEverTick = false;

	bIsProtected = true;
	MinRadius = 0.f;
	MaxRadius = 65.f;
	DecreaseAmount = 0.05f;
	DecreaseRate = 0.1f;
	InitProtectionTime = 10.f;
	PickupProtectionTime = 20.f;
	
	SetupComponents();
}

void AP00_LightActor::SetupComponents()
{
	if (!Root)
	{
		Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

		if (Root)
		{
			RootComponent = Root;	
		}
	}

	if (!SpotLightComponent)
	{
		SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light Componenet"));

		if (SpotLightComponent)
		{
			SpotLightComponent -> SetWorldRotation(FRotator(0.f, -90.f, 0.f));
			SpotLightComponent -> SetIntensity(10000.0f);
			SpotLightComponent -> SetOuterConeAngle(MaxRadius);
			SpotLightComponent -> SetupAttachment(RootComponent);
		}
	}
}

void AP00_LightActor::InitLightActor(UWP00_LightProgressBar* LightProgressBar)
{
	if (CurrentRadius != MaxRadius)
	{
		CurrentRadius = MaxRadius;
		SpotLightComponent -> SetOuterConeAngle(CurrentRadius);
	}

	if (LightProgressBar)
	{
		LightProgressBarPtr = LightProgressBar;
		LightProgressBarPtr -> UpdateProgressBarValue(CurrentRadius/MaxRadius);
		LightProgressBarPtr -> SetBarCooldownValue(1.f);
		
		GetWorld() -> GetTimerManager().SetTimer(ProtectionDelay_TimerHandle, [&]
		{
			LightProgressBarPtr -> SetBarCooldownTimer(InitProtectionTime);
			GetWorld() -> GetTimerManager().SetTimer(Protection_TimerHandle, this, &ThisClass::SetDrainLightTimer, InitProtectionTime, false);
			
		}, 2.f, false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s::InitLightActor: LightProgressBarPtr is NULL"), *GetNameSafe(this));
	}
}

void AP00_LightActor::BeginPlay()
{
	Super::BeginPlay();
}

void AP00_LightActor::BeginDestroy()
{
	Super::BeginDestroy();	
}

void AP00_LightActor::DecreaseLightRadiusOverTime()
{
	if (!bIsProtected)
	{
		if (ensure(SpotLightComponent) && ensure(LightProgressBarPtr))
		{
			CurrentRadius = FMath::Max(CurrentRadius - DecreaseAmount, MinRadius);
		
			SpotLightComponent -> SetOuterConeAngle(CurrentRadius);
			LightProgressBarPtr -> UpdateProgressBarValue(CurrentRadius/MaxRadius);

			if (CurrentRadius == MinRadius)
			{
				if (!OnLightExhausted.ExecuteIfBound())
				{
					UE_LOG(LogTemp, Error, TEXT("%s::DecreaseLightRadiusOverTime: OnLightExhausted wasn't bound to AP00_PlayerCharacter"), *GetNameSafe(this));
				}

				GetWorld() -> GetTimerManager().ClearTimer(DrainLight_TimerHandle);
			}
		}
	}
}

void AP00_LightActor::SetDrainLightTimer()
{
	bIsProtected = false;
	GetWorld() -> GetTimerManager().SetTimer(DrainLight_TimerHandle, this, &ThisClass::DecreaseLightRadiusOverTime, DecreaseRate, true);
}

bool AP00_LightActor::ResetToMaxLightRadius()
{
	if (ensure(SpotLightComponent))
	{
		GetWorld() -> GetTimerManager().ClearTimer(DrainLight_TimerHandle);
		
		CurrentRadius = MaxRadius;
		SpotLightComponent -> SetOuterConeAngle(CurrentRadius);
		LightProgressBarPtr -> UpdateProgressBarValue(CurrentRadius/MaxRadius);
		LightProgressBarPtr -> SetBarCooldownTimer(PickupProtectionTime);
		
		GetWorld() -> GetTimerManager().SetTimer(DrainLight_TimerHandle, this, &ThisClass::DecreaseLightRadiusOverTime, DecreaseRate, true, PickupProtectionTime);
		return true;
	}

	return false;
}

bool AP00_LightActor::ReduceLight(const float& Amount)
{
	if (CurrentRadius > 0.f)
	{
		CurrentRadius = FMath::Max(CurrentRadius - Amount, MinRadius);
		
		SpotLightComponent -> SetOuterConeAngle(CurrentRadius);
		LightProgressBarPtr -> UpdateProgressBarValue(CurrentRadius/MaxRadius);

		return true;
	}

	return false;
}

bool AP00_LightActor::IncreaseLight(const float& Amount)
{
	if (SpotLightComponent && LightProgressBarPtr)
	{
		bIsProtected = true;
		CurrentRadius = FMath::Min(CurrentRadius + Amount, MaxRadius);
		SpotLightComponent -> SetOuterConeAngle(CurrentRadius);
		LightProgressBarPtr -> UpdateProgressBarValue(CurrentRadius/MaxRadius);
		LightProgressBarPtr -> SetBarCooldownTimer(PickupProtectionTime);
		GetWorld() -> GetTimerManager().ClearTimer(DrainLight_TimerHandle);
		GetWorld() -> GetTimerManager().SetTimer(Protection_TimerHandle, this, &ThisClass::SetDrainLightTimer, PickupProtectionTime, false);

		return true;
	}

	return false;
}

bool AP00_LightActor::CanReset() const
{
	return CurrentRadius < MaxRadius;
}

bool AP00_LightActor::GetIsProtected() const
{
	return bIsProtected;
}

void AP00_LightActor::ResetTimers()
{
	GetWorld() -> GetTimerManager().ClearTimer(Protection_TimerHandle);
	GetWorld() -> GetTimerManager().ClearTimer(DrainLight_TimerHandle);
}
