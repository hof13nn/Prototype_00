// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P00_Interactable.h"
#include "GameFramework/Actor.h"
#include "P00_PickupBase.generated.h"

class UBoxComponent;

UCLASS()
class PROTOTYPE_00_API AP00_PickupBase : public AActor, public IP00_Interactable
{
	GENERATED_BODY()

public:
	AP00_PickupBase();

	virtual void StartInteract_Implementation(APawn* InstigatorPawn) override;
	virtual void EndInteract_Implementation(APawn* InstigatorPawn) override;
	
protected:
	virtual void BeginPlay() override;

private:
	void SetupComponents();
	
private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;
};
