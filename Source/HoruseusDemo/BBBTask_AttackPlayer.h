// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BBBTask_AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HORUSEUSDEMO_API UBBBTask_AttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()


protected:
	// to augment existing ExecuteTask method of UBTTaskNode
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
