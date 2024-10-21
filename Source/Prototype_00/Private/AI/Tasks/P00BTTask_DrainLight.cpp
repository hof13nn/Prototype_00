// Fill out your copyright notice in the Description page of Project Settings.


#include "P00BTTask_DrainLight.h"
#include "AIController.h"
#include "P00_ActionBase.h"
#include "P00_ActionHandlerComponent.h"
#include "P00_AICharacter.h"
#include "P00_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UP00BTTask_DrainLight::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (const AAIController* AIController = Cast<AAIController>(OwnerComp.GetAIOwner()); ensure(AIController))
	{
		if (AP00_AICharacter* AIPawn = Cast<AP00_AICharacter>(AIController -> GetPawn()); ensure(AIPawn))
		{
			if (const AP00_PlayerCharacter* TargetActor = Cast<AP00_PlayerCharacter>(OwnerComp.GetBlackboardComponent() -> GetValueAsObject("Target")))
			{
				if (const TSubclassOf<UP00_ActionBase> DrainLightAction = LoadClass<UP00_ActionBase>(AIPawn, TEXT("/Game/Prototype_00/BPs/Actions/BP_Action_DrainLight.BP_Action_DrainLight_C")))
				{
					TargetActor -> GetActionComponent() -> AddAction(AIPawn, DrainLightAction);
					AIPawn -> ExecuteDrainLightEffect();
					BlackboardComponent -> SetValueAsBool("bIsDLApplied", true);

					
					return EBTNodeResult::Succeeded;
				}
			}

			return EBTNodeResult::Failed;
		}

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
	
}
