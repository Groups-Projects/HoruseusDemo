// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class HORUSEUSDEMO_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	void Tick(float DeltaTime);

public:
	void AttackPlayer();
	UFUNCTION()
		AActor* ChooseWaypoint();

private:
	FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere)
		float PatrolDuration = 3.0f;

	UPROPERTY()
		TArray<AActor*> Waypoints;

	UPROPERTY()
		TArray<AActor*> AlertWaypoints;

	UPROPERTY()
		APawn* PlayerPawn;

	UPROPERTY()
		APawn* AIPawn;


	UFUNCTION()
		void RandomPatrol();

	UPROPERTY(EditAnywhere)
		UBehaviorTree* EnemyBehaviorTree; //LN 1.

	UPROPERTY()
		AActor* LookoutPoint; //LN7
};
