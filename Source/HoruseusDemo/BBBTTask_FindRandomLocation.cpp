// Fill out your copyright notice in the Description page of Project Settings.


#include "BBBTTask_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBBBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed; // Failsafe to always return something
	}
	// get the AI actor who uses this task
	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();

	FNavLocation RandomLocation;

	// get navigation system
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	// get a random point within radius from actors location
	NavSys->GetRandomReachablePointInRadius(AIActor->GetActorLocation(), RandomRadius, RandomLocation);
	// set it in blackboard
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomLocation"), RandomLocation);

	return EBTNodeResult::Succeeded;
}
