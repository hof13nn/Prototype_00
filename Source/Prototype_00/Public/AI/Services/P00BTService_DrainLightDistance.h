// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "P00BTService_DrainLightDistance.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_00_API UP00BTService_DrainLightDistance : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category=AI)
	FBlackboardKeySelector TargetActorKey;
	UPROPERTY(EditAnywhere, Category=AI)
	FBlackboardKeySelector DistanceKey;
	UPROPERTY(EditAnywhere, Category=AI)
	float DistanceThreshold;
};
