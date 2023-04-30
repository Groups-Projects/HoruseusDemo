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

	UPROPERTY()
		FVector OwnerVelocityVector;
	UPROPERTY()
		FTransform OwnerTransform;

public:

	// i set it via NativeBeginPlay()
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
		ACharacter *OwnerChara;

	// i set it via UpdateVariables()
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
		float OwnerVelocity = 0.0f;
	// i set it via UpdateVariables()
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
		float OwnerAngle = 0.0f;

private:

	FName NextComboSectionLight;
	FName NextComboSectionHeavy;

	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageIdle;
		
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageHitLight;
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageHitStunned;
		
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageBoxing;
		
	//void ComboCooldownTimerRanOut();
	//FTimerHandle ComboCooldownTimerHandle;

public:

	UFUNCTION( BlueprintCallable )
		void PlayIdle();
		
	UFUNCTION( BlueprintCallable )
		void BreakCombo();
	UFUNCTION( BlueprintCallable )
		void SetNextComboSection( FName Light, FName Heavy );
	UFUNCTION( BlueprintCallable )
		FName GetNextComboSection( int ComboType );

	// i call this via blueprint beh tree task
	/*
	UFUNCTION( BlueprintCallable )
		void PoseSit();
		*/
	/*
	UFUNCTION( BlueprintCallable )
		void StandUpFromChair();
		*/
		
	UFUNCTION( BlueprintCallable )
		void TakeHitLight();
		
	/*
	UFUNCTION( BlueprintCallable )
		void PlayLightAttackCombo();
		*/

public:

	UFUNCTION( BlueprintCallable )
		void UpdateVariables();

private:

	UFUNCTION()
		void NativeBeginPlay() override;
	
};
