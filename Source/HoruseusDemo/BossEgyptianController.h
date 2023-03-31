// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossEgyptianController.generated.h"

/**
 * 
 */
UCLASS()
class HORUSEUSDEMO_API ABossEgyptianController : public AAIController
{
	GENERATED_BODY()
	
public:

	ABossEgyptianController();

protected:

	virtual void BeginPlay() override;
	
public:

	void Tick( float DeltaTime ) override;

private:

	UPROPERTY( EditAnywhere )
		UBehaviorTree* CustomBehaviorTree;
	
};
