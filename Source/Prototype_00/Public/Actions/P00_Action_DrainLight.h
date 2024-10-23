// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P00_ActionEffectBase.h"
#include "UObject/Object.h"
#include "P00_Action_DrainLight.generated.h"

UCLASS()
class PROTOTYPE_00_API UP00_Action_DrainLight : public UP00_ActionEffectBase
{
	GENERATED_BODY()
	
public:
	virtual void ApplyPeriodicEffect(AActor* Instigator) override;
	virtual void StopAction(AActor* Instigator) override;
private:
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float DrainAmount;
};
