// Fill out your copyright notice in the Description page of Project Settings.


#include "BBBTask_AttackPlayer.h"
#include "AIController.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


EBTNodeResult::Type UBBBTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	/*
	if( OwnerComp.GetAIOwner() = nullptr )
	{
		return EBTNodeResult::Failed; // Failsafe to always return something
	}
	*/

	// get pawn
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );

	// get upcasted ai controller
	AEnemyAIController* EnemyAIContr = Cast<AEnemyAIController>( OwnerComp.GetAIOwner() );

	if (EnemyAIContr) {

		// we have upcasted enemy ai controller
		EnemyAIContr->AttackPlayer();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsAttackingRightNow", true);

	}

	OwnerComp.GetBlackboardComponent()->SetValueAsBool("IsAttackingRightNow", false);	

	return EBTNodeResult::Succeeded;
}
