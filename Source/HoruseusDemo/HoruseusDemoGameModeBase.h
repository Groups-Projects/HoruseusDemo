// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HoruseusDemoGameModeBase.generated.h"

class APortal;
class AParticle;
UCLASS()
class HORUSEUSDEMO_API AHoruseusDemoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	//When the player Loses it calls the game over function
	UFUNCTION()
		void GameOver(bool Over);

	UFUNCTION()
		void OpenBossLevel();


	//When the player Wins it calls the Won Game function
	UFUNCTION()
		void WonGame(bool Over);

	//A function that keeps track how many enemies are Destroyed.
	UFUNCTION()
		void EnemyDestroyed();

	//Function that calls how many enemies are left in the HUD.
	UFUNCTION(BlueprintPure)
		float ReturnEnemiesLeft();

	bool levelIsOver = false;

private:
	//Tracks how many enemies the player has Destroyed.
	int EnemyCount = 0;

	//Tracks how many enemies are left when they are destroyed.
	int EnemiesLeft = 8;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APortal> PortalClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AParticle> ParticleClass;

};
