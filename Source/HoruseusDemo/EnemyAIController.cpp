// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	//A reference to the main player.
	APawn* PlayerRef = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), ATargetPoint::StaticClass(), "Patrol_1", Waypoints);
	UE_LOG(LogTemp, Warning, TEXT("found %d Waypoints"), Waypoints.Num());

	if (EnemyBehaviorTree != nullptr)
	{
		RunBehaviorTree(EnemyBehaviorTree);
	}

	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerRef->GetActorLocation());
	GetBlackboardComponent()->SetValueAsVector(TEXT("HomePosition"), GetPawn()->GetActorLocation());
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAIController::AttackPlayer()
{
	AMyCharacter* EnemyPlayer = Cast<AMyCharacter>(GetPawn());

	if (EnemyPlayer)
	{
		EnemyPlayer->Attack();
	}
}

AActor* AEnemyAIController::ChooseWaypoint()
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Waypoints[index];
}

void AEnemyAIController::RandomPatrol()
{
	MoveToActor(ChooseWaypoint());
}