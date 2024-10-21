// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "P00_PickupBase.h"
#include "P00_Pickup_DoorKey.generated.h"

UCLASS()
class PROTOTYPE_00_API AP00_Pickup_DoorKey : public AP00_PickupBase
{
	GENERATED_BODY()

public:
	virtual void StartInteract_Implementation(APawn* InstigatorPawn) override;
	virtual void EndInteract_Implementation(APawn* InstigatorPawn) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Tags")
	FGameplayTag KeyTag;
};
