// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossEgyptianAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class HORUSEUSDEMO_API UBossEgyptianAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageIdle;
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageAttackLight;
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageAttackHeavy;
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageTaunt;
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageHitTaken;
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageDeath;
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageKilledSomeone;

public:

	UFUNCTION( BlueprintCallable )
		void PlayIdle();
		
	UFUNCTION( BlueprintCallable )
		void BeginFight();

	UFUNCTION( BlueprintCallable )
		void TakeHitLight();
	
};
