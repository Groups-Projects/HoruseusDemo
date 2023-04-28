// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "MyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AMyCharacter>(GetPawn());
	HUD = CreateWidget(this, ClassHUD);
	PauseWidget = CreateWidget(this, PauseMenuHUDClass);

	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
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
	InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallSprint);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACustomPlayerController::CallStopSprinting);
	InputComponent->BindAction("Crouching", EInputEvent::IE_Pressed, this, &ACustomPlayerController::CallCrouching);
	InputComponent->BindAction("Crouching", EInputEvent::IE_Released, this, &ACustomPlayerController::CallStopCrouching);
	InputComponent->BindAction("Pause", EInputEvent::IE_Pressed, this, &ACustomPlayerController::PauseGame);
}

void ACustomPlayerController::CallForward(float Value)
{
	if (Player) 
	{
		Player->MoveForward(Value);
	}
}

void ACustomPlayerController::CallStrafe(float Value)
{
	if (Player) 
	{
		Player->MoveStrafe(Value);
	}
}

void ACustomPlayerController::CallTurn(float Value)
{
	if (Player) 
	{
		Player->Turn(Value);
	}
}

void ACustomPlayerController::CallLookUp(float Value)
{
	if (Player) 
	{
		Player->LookUp(Value);
	}
}

void ACustomPlayerController::CallFire()
{
	if (Player) 
	{
		Player->Attack();
	}
}

void ACustomPlayerController::CallJump()
{
	if (Player) 
	{
		if (Player->canMove==true)
		{
			Player->Jump();
		}
	}
}

void ACustomPlayerController::CallSprint()
{
	if (Player) 
	{
		Player->Sprint();
	}
}

void ACustomPlayerController::CallStopSprinting()
{
	if (Player) 
	{
		Player->StopSprinting();
	}
}

void ACustomPlayerController::CallCrouching()
{
	if (Player) 
	{
		Player->Crouching();
	}
}

void ACustomPlayerController::CallStopCrouching()
{
	if (Player) 
	{
		Player->StopCrouching();
	}
}

void ACustomPlayerController::PauseGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (PauseMenuHUDClass)
	{
		PauseWidget->AddToViewport();
		APlayerController* Controller = UGameplayStatics::GetPlayerController(Player, 0);
		Controller->SetShowMouseCursor(true);
	}
}

