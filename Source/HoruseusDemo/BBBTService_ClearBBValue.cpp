// Fill out your copyright notice in the Description page of Project Settings.


#include "BBBTService_ClearBBValue.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBBBTService_ClearBBValue::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey()); \
}