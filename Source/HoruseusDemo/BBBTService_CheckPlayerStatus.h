// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BBBTService_CheckPlayerStatus.generated.h"

/**
 * 
 */
UCLASS()
class HORUSEUSDEMO_API UBBBTService_CheckPlayerStatus : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	// reused code from CO2301 assignment 1

private:
	
	bool PlayerIsInFrontOfMe( APawn *SelfPawn, APawn *LivePawn );

protected:

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTService_PlayerLocationIfSeen.h

	virtual void TickNode(
		UBehaviorTreeComponent &OwnerComp,
		uint8 *NodeMemory,
		float DeltaSeconds ) override;

};
