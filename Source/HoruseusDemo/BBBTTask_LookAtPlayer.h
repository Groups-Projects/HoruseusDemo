// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BBBTTask_LookAtPlayer.generated.h"

/**
 * 
 */
UCLASS()
class HORUSEUSDEMO_API UBBBTTask_LookAtPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTTask_ClearBlackboardValue.h

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent &OwnerComp,
		uint8 *NodeMemory
		) override;
	
};
