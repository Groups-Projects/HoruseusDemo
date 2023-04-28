// Fill out your copyright notice in the Description page of Project Settings.


#include "BBBTTask_FindRandomWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"


EBTNodeResult::Type UBBBTTask_FindRandomWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed; // Failsafe to always return something
	}
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (Cast<AEnemyAIController>(AIController))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(
			TEXT("Waypoint"),
			Cast<AEnemyAIController>(AIController)->ChooseWaypoint()->GetActorLocation());
	}
	return EBTNodeResult::Succeeded;
}
