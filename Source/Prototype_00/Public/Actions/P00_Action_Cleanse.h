// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P00_ActionBase.h"
#include "P00_PlayerCharacter.h"
#include "P00_Action_Cleanse.generated.h"

class USoundCue;
class USphereComponent;

UCLASS()
class PROTOTYPE_00_API UP00_Action_Cleanse : public UP00_ActionBase
{
	GENERATED_BODY()
	UP00_Action_Cleanse();
	void ExecuteCleanse(AP00_PlayerCharacter* Instigator);

public:
	virtual void StartAction(AActor* Instigator) override;
	virtual void StopAction(AActor* Instigator) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Action | Params")
	float LightCost;
	UPROPERTY(EditDefaultsOnly, Category = "Action | Animation")
	UAnimMontage* ActionMontage;
	UPROPERTY(EditAnywhere, Category= "Action | Animation")
	float CleanseAnimDelay;
	UPROPERTY(EditDefaultsOnly, Category = "Action | VFX")
	UParticleSystem* ParticleSystem;
	UPROPERTY(EditDefaultsOnly, Category = "Action | VFX")
	USoundCue* SpellSound;
	UPROPERTY(EditAnywhere, Category= "Action | Trace")
	TEnumAsByte<ECollisionChannel> QueryChannel;
	UPROPERTY(EditAnywhere, Category= "Action | Trace")
	float TraceRadius;
};
