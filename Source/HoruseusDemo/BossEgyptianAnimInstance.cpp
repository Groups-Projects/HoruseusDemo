// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEgyptianAnimInstance.h"

void UBossEgyptianAnimInstance::TakeHitLight() {

	if( !MontageHitTaken ) {
		// no montage, nothing to do
		return;
	}

	Montage_Play( MontageHitTaken, 1.0f );

}

void UBossEgyptianAnimInstance::PlayIdle() {

	// Continuously plays through idle montage.

	//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PlayIdle") );

	// make sure i have the montage
	if( !MontageIdle ) {
		// no montage, nothing to do
		UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PlayIdle no MontageIdle") );
		return;
	}

	if( Montage_IsPlaying( MontageIdle ) ) {
		// slot occupied, nothing to do
		//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PlayIdle occupied") );
		return;
		
	}
	
	UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PlayIdle ok") );

	// play the montage
	Montage_Play( MontageIdle, 1.0f, EMontagePlayReturnType::Duration, 0.0f, false );

	// but instruct the montage to
	// cycle through the "Default" section perpetually
	Montage_SetNextSection( FName("Default"), FName("Default"), MontageIdle );

}

void UBossEgyptianAnimInstance::BeginFight() {

	// Transitions from idle to fighting.

	// make sure i have the montage
	if( !MontageIdle ) {
		// no montage, nothing to do
		UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::BeginFight no MontageIdle") );
		return;
	}
	
	UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::BeginFight going from idle") );

	// finish all montages quickly
	// help:
	// https://forums.unrealengine.com/t/blend-anim-montage-sections/332654/10
	StopAllMontages( 0.5f );

	// but instruct the montage to
	// cycle through sections
	Montage_SetNextSection( FName("Default"), FName("StandUp"), MontageIdle );
	Montage_SetNextSection( FName("StandUp"), FName("End"), MontageIdle );

	UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::BeginFight finished") );

}
