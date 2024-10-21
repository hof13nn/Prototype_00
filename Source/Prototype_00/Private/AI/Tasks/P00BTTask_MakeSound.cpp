// Fill out your copyright notice in the Description page of Project Settings.


#include "P00BTTask_MakeSound.h"
#include "AIController.h"
#include "P00_AICharacter.h"

EBTNodeResult::Type UP00BTTask_MakeSound::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner());

	if (ensure(AIController))
	{
		AP00_AICharacter* AIPawn = Cast<AP00_AICharacter>(AIController -> GetPawn());
		
		if (AIPawn )
		{
			AIPawn -> MakeSound();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
