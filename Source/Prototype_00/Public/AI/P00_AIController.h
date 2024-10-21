// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "P00_AIController.generated.h"

class UBehaviorTree;

UCLASS()
class PROTOTYPE_00_API AP00_AIController : public AAIController
{
	GENERATED_BODY()

	AP00_AIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category= "AI")
	UBehaviorTree* BehaviorTree;
};
