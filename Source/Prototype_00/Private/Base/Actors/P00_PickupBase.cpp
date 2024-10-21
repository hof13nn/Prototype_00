// Fill out your copyright notice in the Description page of Project Settings.

#include "P00_PickupBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

AP00_PickupBase::AP00_PickupBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SetupComponents();
}

void AP00_PickupBase::StartInteract_Implementation(APawn* InstigatorPawn)
{
}

void AP00_PickupBase::EndInteract_Implementation(APawn* InstigatorPawn)
{

}

void AP00_PickupBase::SetupComponents()
{
	if (!BoxComponent)
	{
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

		if (BoxComponent)
		{
			RootComponent = BoxComponent;
		}
	}

	if (!MeshComponent)
	{
		MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));

		if (MeshComponent)
		{
			MeshComponent -> SetupAttachment(RootComponent);
		}
	}

	if (!ParticleSystemComponent)
	{
		ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));

		if (ParticleSystemComponent)
		{
			ParticleSystemComponent -> SetupAttachment(MeshComponent);
		}
	}
}

void AP00_PickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}