// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"
class UUserWidget;
class AMyCharacter;
class AMyCharacter;


UCLASS()
class HORUSEUSDEMO_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent();
	virtual void CallForward(float Value);
	virtual void CallStrafe(float Value);
	virtual void CallTurn(float Value);
	virtual void CallLookUp(float Value);
	virtual void CallFire();
	virtual void CallJump();

	virtual void CallSprint();
	virtual void CallStopSprinting();

	AMyCharacter* Player;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ClassHUD;

	UUserWidget* HUD;


};
