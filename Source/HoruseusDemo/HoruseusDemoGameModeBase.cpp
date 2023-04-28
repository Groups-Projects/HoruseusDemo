// Copyright Epic Games, Inc. All Rights Reserved.


#include "HoruseusDemoGameModeBase.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Portal.h"
#include "Particle.h"

void AHoruseusDemoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AHoruseusDemoGameModeBase::GameOver(bool)
{
	//When the player loses the player gets trasnfered to another world which is prompted a game over screen.
	UE_LOG(LogTemp, Warning, TEXT("Game Over"));
	UGameplayStatics::OpenLevel(GetWorld(), "EndLevel");
}

void AHoruseusDemoGameModeBase::WonGame(bool Over)
{
	//When the player wins the player gets trasnfered to another world which is prompted a You won screen.
	UE_LOG(LogTemp, Warning, TEXT("You won"));
	UGameplayStatics::OpenLevel(GetWorld(), "VictoryLevel");
}


void AHoruseusDemoGameModeBase::EnemyDestroyed()
{
	//Keeps track how many enemies are Destroyed.
	EnemyCount += 1;
	//Keeps track how many enemies are left alive.
	EnemiesLeft -= 1;

	//If the player has destroyed more than nine enemies the game calls the Won game Function.
	if (EnemiesLeft <= 0)
	{
		GetWorld()->SpawnActor<AParticle>(ParticleClass, FVector{ 660.0f,-1110.0f,110.0f }, FRotator{ 0.0f,0.0f,0.0f });
		levelIsOver = true;
		GetWorld()->SpawnActor<APortal>(PortalClass, FVector{ 645.0f,-1140.0f,50.0f }, FRotator{0.0f,0.0f,0.0f});
		/*FTimerHandle timer;
		GetWorldTimerManager().SetTimer(timer, this, &AHoruseusDemoGameModeBase::OpenBossLevel, 5.0f, false);*/
	}
}

float AHoruseusDemoGameModeBase::ReturnEnemiesLeft()
{
	//returns how many enemies are left and gets transfred to the players screen.
	return EnemiesLeft;
}

void AHoruseusDemoGameModeBase::OpenBossLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Boss_Level");
	EnemiesLeft = 1;
}