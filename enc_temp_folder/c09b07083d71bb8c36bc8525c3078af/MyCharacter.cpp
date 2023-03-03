// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 300.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}


void AMyCharacter::MoveForward(float Axis)
{
	if (Health >= 0.0f) {
		AddMovementInput(GetActorForwardVector() * Axis);
	}
}

void AMyCharacter::MoveStrafe(float Axis)
{
	if (Health >= 0.0f) {
		AddMovementInput(GetActorRightVector() * Axis);
	}
}

void AMyCharacter::Turn(float Axis)
{
	if (Health >= 0.0f) {
		AddControllerYawInput(Axis);
	}
}

void AMyCharacter::LookUp(float Axis)
{
	if (Health >= 0.0f) {
		AddControllerPitchInput(Axis);
	}
}

void AMyCharacter::Fire()
{

		UE_LOG(LogTemp, Warning, TEXT("Bullet fired."));
}



