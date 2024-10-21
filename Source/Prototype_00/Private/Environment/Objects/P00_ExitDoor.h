// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "P00_ExitDoor.generated.h"

class UBoxComponent;

UCLASS()
class PROTOTYPE_00_API AP00_ExitDoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AP00_ExitDoor();

protected:
	virtual void PostInitializeComponents() override;
private:
	void SetupComponents();
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer KeyTags;
	UPROPERTY(EditDefaultsOnly)
	USoundCue* UnlockedSound;
	UPROPERTY(EditDefaultsOnly)
	USoundCue* DoorOpenSound;
	UPROPERTY(EditDefaultsOnly)
	float DoorOpenDelay;
	FTimerHandle DoorOpen_TimerHandle;
};
