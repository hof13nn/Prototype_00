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
	void DeactivateAI();
	void Cleanse(AP00_PlayerCharacter* PlayerCharacter);
	void AddStoredLight(const float& Value);
	
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	void SetupComponents();
	void SetTarget(AActor* NewTarget);
	
private:
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);
	
private:
	bool bIsAlive;
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensingComponent;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AP00_Pickup_LightEnergy> LightEnergyClass;
	UPROPERTY(EditAnywhere, Category= "AI")
	FName DrainLightName;
	UPROPERTY(EditAnywhere, Category= "AI")
	USoundCue* MinionSound;
	UPROPERTY(VisibleAnywhere)
	float StoredLight;
};
