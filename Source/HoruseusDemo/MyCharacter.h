// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ASceptor;
class UAnimMontage;
class USceneCaptureComponent2D;
class AEnemyAIController;
class AParticle;
UCLASS()
class HORUSEUSDEMO_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	//UPROPERTY(Edit)
	ASceptor* ScWeapon;
	AEnemyAIController* EnemyCont;
	void MoveForward(float Axis);
	void MoveStrafe(float Axis);
	void Turn(float Axis);
	void LookUp(float Axis);
	//void Attack_1();
	//void Attack_2();
	//void Attack_3();
	//void GeneralMontageTimerHandleRanOut();
	void ActorDestroy();
	void HealthPickup();
	void Attack_End();
	
	UFUNCTION(BlueprintPure)
		float ReturnStamina();

	UFUNCTION(BlueprintPure)
		float ReturnHealth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
		int iComboState;

	FTimerHandle GeneralMontageTimerHandle;

	UPROPERTY(EditAnywhere)
		int GeneralMontageTimerValue = 20.0f;

	UPROPERTY(EditAnywhere)
		bool IsInAttack;

	UPROPERTY(EditAnywhere)
		int AttackNum;

	UPROPERTY(EditAnywhere)
		float TurnRate = 45.0f;

	UPROPERTY(EditAnywhere)
		float LookupRate = 45.0f;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;

	//Creating a USpringArmComponent for the mini map camera.
	UPROPERTY(EditAnywhere)
		USpringArmComponent* MiniMapArm;

	//Creating a USceneCaptureComponent2D to create a mini map camera.
	UPROPERTY(EditAnywhere)
		USceneCaptureComponent2D* MiniMapCamera;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASceptor> ScWeaponClass;

    UPROPERTY(EditAnywhere)
		UAnimMontage* AttackMontage;

    UPROPERTY(EditAnywhere)
        UAnimMontage* AttackMontage_2;

    UPROPERTY(EditAnywhere)
       UAnimMontage* AttackMontage_3;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* GetHitMontage;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* DyingMontage;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		class USoundBase* CrystalPickUpSound;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void Sprint();
	void StopSprinting();
	void RefillStamina();
	void HandleSprinting();
	void Crouching();
	void StopCrouching();

	FTimerHandle RegenerateStamina;
	FTimerHandle LowerStamina;

	UPROPERTY(EditAnywhere)
		float Stamina = 100.f;

	UPROPERTY()
		bool bPlayerIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayerCanCrouch=false;

	UPROPERTY(EditAnywhere)
		bool canMove;

	UPROPERTY(EditAnywhere)
		float health;
	
	UFUNCTION(BlueprintCallable)  // to be used by AI
	void Attack();

	UPROPERTY(EditAnywhere)
		TSubclassOf<AParticle> ParticleClass;
};
