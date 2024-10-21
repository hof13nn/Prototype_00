// Fill out your copyright notice in the Description page of Project Settings.


#include "P00_AIController.h"

AP00_AIController::AP00_AIController()
{
	PrimaryActorTick.bCanEverTick = true;
	BehaviorTree = nullptr;
}

void AP00_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ensureMsgf(BehaviorTree, TEXT("AAR_AIController::OnPossess: BT is NULL")))
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AP00_AIController::BeginPlay()
{
	Super::BeginPlay();
}
