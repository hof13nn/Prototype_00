// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P00_ActionBase.h"
#include "P00_ActionEffectBase.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_00_API UP00_ActionEffectBase : public UP00_ActionBase
{
	GENERATED_BODY()

public:
	virtual void StartAction(AActor* Instigator) override;
	virtual void StopAction(AActor* Instigator) override;
	
protected:
	virtual void ApplyPeriodicEffect(AActor* Instigator);
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect", meta=(AllowPrivateAccess="true"))
	float Duration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effect", meta=(AllowPrivateAccess="true"))
	float Rate;

protected:
	FTimerHandle EffectDuration_TimerHandle;
	FTimerHandle EffectRate_TimerHandle;
};
