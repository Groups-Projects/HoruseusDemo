// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ASceptor;
class UAnimMontage;

UCLASS()
class HORUSEUSDEMO_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	//UPROPERTY(Edit)
	ASceptor* ScWeapon;

	void MoveForward(float Axis);
	void MoveStrafe(float Axis);
	void Turn(float Axis);
	void LookUp(float Axis);
	void Fire();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASceptor> ScWeaponClass;

	UPROPERTY(EditAnywhere)
		UAnimMontage* AttackMontage;
		


	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		float Health = 100.0f;
};
