// Fill out your copyright notice in the Description page of Project Settings.


#include "BP00BTTask_StopDrainLight.h"

#include "AIController.h"
#include "P00_ActionHandlerComponent.h"
#include "P00_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

class AP00_AICharacter;

EBTNodeResult::Type UBP00BTTask_StopDrainLight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (const AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner()))
	{
		if (AP00_AICharacter* AIPawn = Cast<AP00_AICharacter>(AIController -> GetPawn()))
		{
			if (const AP00_PlayerCharacter* TargetActor = Cast<AP00_PlayerCharacter>(OwnerComp.GetBlackboardComponent() -> GetValueAsObject("Target")))
			{
				AIPawn -> StopDrainLightEffect();
				BlackboardComponent -> SetValueAsBool("bIsDLApplied", false);
				TargetActor -> GetActionComponent() -> StopActionByName(AIPawn, AIPawn -> GetDrainLightName());
				return EBTNodeResult::Succeeded;
			}
			
			return EBTNodeResult::Failed;
		}

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
	
}