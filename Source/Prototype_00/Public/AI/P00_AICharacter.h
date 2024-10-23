// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P00_BaseCharacter.h"
#include "P00_PlayerCharacter.h"
#include "P00_AICharacter.generated.h"

class USoundCue;
class AP00_Pickup_LightEnergy;
class UPawnSensingComponent;

UCLASS()
class PROTOTYPE_00_API AP00_AICharacter : public AP00_BaseCharacter
{
	GENERATED_BODY()

public:
	AP00_AICharacter();

	void MakeSound();
	void ExecuteDrainLightEffect();
	void StopDrainLightEffect();
	void DeactivateAI();
	void Cleanse(AP00_PlayerCharacter* PlayerCharacter);
	void AddStoredLight(const float& Value);
	FName GetDrainLightName() const;
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	void SetupComponents();
	void SetTarget(AActor* NewTarget);
	
private:
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);
	UFUNCTION()
	void OnHearPawn(APawn* InstigatorActor, const FVector& Location, float Volume);
	
private:
	bool bIsAlive;
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensingComponent;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;
	UPROPERTY(EditDefaultsOnly, Category= "Enemy | Pickup")
	TSubclassOf<AP00_Pickup_LightEnergy> LightEnergyClass;
	UPROPERTY(EditAnywhere, Category= "Enemy | Spell")
	FName DrainLightName;
	UPROPERTY(EditAnywhere, Category= "Enemy | Spell")
	UAnimMontage* DrainLightAnim;
	UPROPERTY(EditAnywhere, Category= "Enemy | Sound")
	USoundCue* MinionSound;
	UPROPERTY(VisibleAnywhere)
	float StoredLight;

	FTimerHandle DestroyAI_TimerHandle;
};
