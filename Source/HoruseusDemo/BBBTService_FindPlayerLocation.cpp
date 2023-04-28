// Fill out your copyright notice in the Description page of Project Settings.


#include "BBBTService_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBBBTService_FindPlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
	{
		OwnerComp.GetBlackboardComponent()->
			SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation()-20.0f);
	}
}
