// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "MyCharacter.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AMyCharacter>(GetPawn());
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAxis("ForwardMovement", this, &ACustomPlayerController::CallForward);
	InputComponent->BindAxis("StrafeMovement", this, &ACustomPlayerController::CallStrafe);
	InputComponent->BindAxis("Turning", this, &ACustomPlayerController::CallTurn);
	InputComponent->BindAxis("LookUp", this, &ACustomPlayerController::CallLookUp);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallFire);
	InputComponent->BindAction("Jumping", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallJump);
}

void ACustomPlayerController::CallForward(float Value)
{
	if (Player) {
		Player->MoveForward(Value);
	}
}

void ACustomPlayerController::CallStrafe(float Value)
{
	if (Player) {
		Player->MoveStrafe(Value);
	}
}

void ACustomPlayerController::CallTurn(float Value)
{
	if (Player) {
		Player->Turn(Value);
	}
}

void ACustomPlayerController::CallLookUp(float Value)
{
	if (Player) {
		Player->LookUp(Value);
	}
}

void ACustomPlayerController::CallFire()
{
	if (Player) {
		Player->Attack();
	}
}

void ACustomPlayerController::CallJump()
{
	if (Player) {
		Player->Jump();
	}
}

