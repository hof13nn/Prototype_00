// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_ExitDoor.h"

#include "P00_ActionHandlerComponent.h"
#include "P00_PlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


AP00_ExitDoor::AP00_ExitDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	UnlockedSound = nullptr;
	DoorOpenSound = nullptr;
	DoorOpenDelay = 1.f;
	SetupComponents();
}

void AP00_ExitDoor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BoxComponent)
	{
		BoxComponent -> OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	}
}

void AP00_ExitDoor::SetupComponents()
{
	if (!Root)
	{
		Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

		if (Root)
		{
			RootComponent = Root;
		}
	}

	if (!StaticMeshComponent)
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));

		if (StaticMeshComponent)
		{
			StaticMeshComponent -> SetupAttachment(RootComponent);
		}
	}

	if (!BoxComponent)
	{
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

		if (BoxComponent)
		{
			BoxComponent -> SetupAttachment(StaticMeshComponent);
		}
	}
}

void AP00_ExitDoor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AP00_PlayerCharacter* PC = Cast<AP00_PlayerCharacter>(OtherActor))
	{
		if (PC -> GetActionComponent() -> HasTags(KeyTags))
		{
			GEngine -> AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("You win"));
			UGameplayStatics::PlaySoundAtLocation(this, UnlockedSound, GetActorLocation());
			//GetWorld() -> GetTimerManager().SetTimer(DoorOpen_TimerHandle, [&] {	UGameplayStatics::PlaySoundAtLocation(this, DoorOpenSound, GetActorLocation()); }, DoorOpenDelay, false);
		}
	}
}
