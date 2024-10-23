// Fill out your copyright notice in the Description page of Project Settings.

#include "P00BTService_CheckKey.h"
#include "P00_ActionHandlerComponent.h"
#include "P00_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void UP00BTService_CheckKey::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (ensure(BlackboardComponent))
	{
		if (AP00_PlayerCharacter* TargetActor = Cast<AP00_PlayerCharacter>(BlackboardComponent -> GetValueAsObject(TargetActorKey.SelectedKeyName)))
		{
			UP00_ActionHandlerComponent* AC = TargetActor -> GetActionComponent();

			if (AC)
			{
				BlackboardComponent -> SetValueAsBool(OwnTagKey.SelectedKeyName, AC -> HasKeyTag(KeyTag));
			}
		}
	}
}
