// Fill out your copyright notice in the Description page of Project Settings.


#include "BBBTService_LineOfSight.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBBBTService_LineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* EnemyAIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = EnemyAIController->GetPawn();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn && AIPawn)
	{
		FVector AIForwardVector = AIPawn->GetActorForwardVector(); //already normalised
		FVector PlayerPositionVector = PlayerPawn->GetActorLocation();
		FVector AIPositionVector = AIPawn->GetActorLocation();
		FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;
		AIToPlayerVector.Normalize(); //this vector must be explicitly normalised

		float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);

		// check if player pawn is in line of sight and +/-60 degrees in front of the enemy  TODO: distance?
		if (EnemyAIController->LineOfSightTo(PlayerPawn, FVector(0, 0, 0), false) && DirectionDotProduct > 0.5f)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		}
	}
}
