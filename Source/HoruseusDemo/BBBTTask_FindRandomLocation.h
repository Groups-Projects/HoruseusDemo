// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BBBTTask_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class HORUSEUSDEMO_API UBBBTTask_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	// to augment existing ExecuteTask method of UBTTaskNode
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
		float RandomRadius = 2000.0f;
};
