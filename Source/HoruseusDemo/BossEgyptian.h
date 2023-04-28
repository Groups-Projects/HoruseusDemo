// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossEgyptianController.h"
#include "BossEgyptianAnimInstance.h"
#include "BossEgyptian.generated.h"

class UAnimMontage;
class UAnimBlueprint;
class AParticle;
UCLASS()
class HORUSEUSDEMO_API ABossEgyptian : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossEgyptian();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	// reused code from CO2301 assignment 1

	// reused code from CO2301 lab with saucers
	
	virtual float TakeDamage(
		float DamageAmount,
		const struct FDamageEvent& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
		) override;
		
	// editable properties
	
	UPROPERTY( EditAnywhere )
		float MoveSpeed = 1000.0f;
	UPROPERTY( EditAnywhere )
		float RotationSpeed = 100.0f;

	UPROPERTY( EditAnywhere )
		float StatsBaseHP = 100.0f;
	UPROPERTY( EditAnywhere )
		float StatsBaseDamage = 100.0f;
		
	// i want to easily see some things

	UPROPERTY( VisibleAnywhere )
		class ABossEgyptianController *CustomAIController;
	
	UPROPERTY( VisibleAnywhere )
		UBossEgyptianAnimInstance* CustomAnimInstance;
		
	// help:
	// https://en.cppreference.com/w/cpp/language/nested_types
	struct CustomStates {
		const static int Idle = 0;
		const static int InFight = 1;
		const static int Boxing = 2;
	};
	
	UPROPERTY( VisibleAnywhere )
		int CurrentCustomState = CustomStates::Idle;
		
	UPROPERTY( EditAnywhere )
		USoundBase *SoundAttackLight = nullptr;
	UPROPERTY( EditAnywhere )
		USoundBase *SoundAttackHeavy = nullptr;
	UPROPERTY( EditAnywhere )
		USoundBase *SoundTaunt = nullptr;
	UPROPERTY( EditAnywhere )
		USoundBase *SoundHitTaken = nullptr;
	UPROPERTY( EditAnywhere )
		USoundBase *SoundDeath = nullptr;
	UPROPERTY( EditAnywhere )
		USoundBase *SoundKilledSomeone = nullptr;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AParticle> ParticleClass;

public:

	UFUNCTION( BlueprintCallable )
		int GetCurrentCustomState();

	UFUNCTION( BlueprintCallable )
		float GetStatsHP();
	UFUNCTION( BlueprintCallable )
		float GetStatsDamage();

	// listen to specific signals

	// help:
	// bing/new prompt "how do i use AnimInstance->OnPlayMontageNotifyEnd.AddDynamic()?"
	// result:
	/*
	AnimInstance->OnPlayMontageNotifyEnd.AddDynamic() is a way to bind a function to the OnPlayMontageNotifyEnd delegate of an AnimInstance1. This delegate is called when a montage hits a ÅePlayMontageNotifyÅf or ÅePlayMontageNotifyWindowÅf end2. The function that you bind to this delegate must have the same signature as the FPlayMontageAnimNotifyDelegate class, which is:

	void FunctionName(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload, UAnimMontage* Montage, bool bEndOfSection);

	The function name can be any valid identifier, but the parameters must match the delegate signature. The parameters are: the name of the notify, the branching point payload that contains information about the montage instance and the notify state, the montage that triggered the notify, and a boolean flag that indicates whether the notify is at the end of a section or not.

	To use AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(), you need to pass a pointer to an object that has the function you want to bind, and a pointer to that function. For example:

	AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &AMyCharacter::MyFunction);

	This will bind MyFunction of AMyCharacter class to the OnPlayMontageNotifyEnd delegate of AnimInstance. Whenever a montage ends with a ÅePlayMontageNotifyÅf or ÅePlayMontageNotifyWindowÅf, MyFunction will be called with the appropriate parameters.
	*/
	UFUNCTION()
		void OnMontageHitTakenEnd(
			FName NotifyName,
			const FBranchingPointNotifyPayload& BranchingPointPayload
			// function signature changed - got this from
			// error while compiling
			//UAnimMontage* Montage,
			//bool bEndOfSection
		);

};
