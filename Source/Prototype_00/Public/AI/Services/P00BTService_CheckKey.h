// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "P00BTService_CheckKey.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_00_API UP00BTService_CheckKey : public UBTService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category=AI)
	FBlackboardKeySelector TargetActorKey;
	UPROPERTY(EditAnywhere, Category=AI)
	FBlackboardKeySelector OwnTagKey;
	UPROPERTY(EditAnywhere, Category=AI)
	FGameplayTag KeyTag;
};
