// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WP00_LightProgressBar.h"
#include "GameFramework/Actor.h"
#include "P00_LightActor.generated.h"

class UWP00_LightProgressBar;
class USpotLightComponent;

DECLARE_DELEGATE(FOnLightExhausted)

UCLASS()
class PROTOTYPE_00_API AP00_LightActor : public AActor
{
	GENERATED_BODY()

public:
	AP00_LightActor();

	void InitLightActor(UWP00_LightProgressBar* LightProgressBar);
	bool ResetToMaxLightRadius();
	bool ReduceLight(const float& Amount);
	bool IncreaseLight(const float& Amount);
	bool CanReset() const;
	bool GetIsProtected() const;
	void ResetTimers();
	
protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
private:
	void SetupComponents();
	void DecreaseLightRadiusOverTime();
	void SetDrainLightTimer();
	
public:
	FOnLightExhausted OnLightExhausted;
	
private:
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* SpotLightComponent;
	UPROPERTY(VisibleAnywhere)
	UWP00_LightProgressBar* LightProgressBarPtr;
	UPROPERTY(EditAnywhere, Category= "Settings")
	bool bIsProtected;
	UPROPERTY(EditAnywhere, Category= "Settings")
	float MaxRadius;
	UPROPERTY(EditAnywhere, Category= "Settings")
	float MinRadius;
	UPROPERTY(EditAnywhere, Category= "Settings")
	float CurrentRadius;
	UPROPERTY(EditAnywhere, Category= "Settings")
	float DecreaseAmount;
	UPROPERTY(EditAnywhere, Category= "Settings")
	float DecreaseRate;
	UPROPERTY(EditAnywhere, Category= "Settings")
	float InitProtectionTime;
	UPROPERTY(EditAnywhere, Category= "Settings")
	float PickupProtectionTime;
	FTimerHandle DrainLight_TimerHandle;
	FTimerHandle ProtectionDelay_TimerHandle;
	FTimerHandle Protection_TimerHandle;
};
