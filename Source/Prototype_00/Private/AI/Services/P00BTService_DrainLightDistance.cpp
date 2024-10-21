// Fill out your copyright notice in the Description page of Project Settings.


#include "P00BTService_DrainLightDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UP00BTService_DrainLightDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                                float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (ensure(BlackboardComponent))
	{
		if (AActor* TargetActor = Cast<AActor>(BlackboardComponent -> GetValueAsObject(TargetActorKey.SelectedKeyName)))
		{
			AAIController* AIController = OwnerComp.GetAIOwner();

			if (ensure(AIController))
			{
				APawn* AIPawn = AIController -> GetPawn();

				if (ensure(AIPawn))
				{
					float Distance = FVector::Distance(TargetActor -> GetActorLocation(), AIPawn -> GetActorLocation());

					BlackboardComponent -> SetValueAsBool(DistanceKey.SelectedKeyName, Distance < DistanceThreshold && AIController -> LineOfSightTo(TargetActor));
				}
				else
				{
					BlackboardComponent -> SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);
					BlackboardComponent -> SetValueAsBool(DistanceKey.SelectedKeyName, false);
				}
			}
		}
	}
}
