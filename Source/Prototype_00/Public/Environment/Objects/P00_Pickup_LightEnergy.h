// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P00_PickupBase.h"
#include "P00_Pickup_LightEnergy.generated.h"

UCLASS()
class PROTOTYPE_00_API AP00_Pickup_LightEnergy : public AP00_PickupBase
{
	GENERATED_BODY()

public:
	AP00_Pickup_LightEnergy();
	
	virtual void StartInteract_Implementation(APawn* InstigatorPawn) override;
	virtual void EndInteract_Implementation(APawn* InstigatorPawn) override;

	void SetLightAmount(const float& Value);
private:
	UPROPERTY(EditDefaultsOnly, Category=Params)
	float LightAmount;
};
