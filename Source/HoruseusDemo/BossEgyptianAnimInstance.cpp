// Fill out your copyright notice in the Description page of Project Settings.

// header
#include "BossEgyptianAnimInstance.h"
// default
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
// custom

void UBossEgyptianAnimInstance::TakeHitLight() {

	if( !MontageHitLight ) {
		// no montage, nothing to do
		UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::TakeHitLight no MontageHitLight, not doing anything") );
		return;
	}
	
	//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::TakeHitLight start") );

	Montage_Play( MontageHitLight, 1.0f );
	
	//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::TakeHitLight end") );

}

void UBossEgyptianAnimInstance::SetNextComboSection( FName Light, FName Heavy ) {

	NextComboSectionLight = Light;
	NextComboSectionHeavy = Heavy;

}

void UBossEgyptianAnimInstance::BreakCombo() {

	SetNextComboSection( TEXT("None"), TEXT("None") );
	//ComboCooldownTimerRanOut();

}

FName UBossEgyptianAnimInstance::GetNextComboSection( int ComboType ) {

	if( ComboType==0 ) {
		// light
		return NextComboSectionLight;
	}
	else if( ComboType==1 ) {
		// heavy
		return NextComboSectionHeavy;
	}
	else {
		// unknown
		return TEXT("None");
	}

}

/*
void UBossEgyptianAnimInstance::ComboCooldownTimerRanOut() {

	// this will allow to set this timer again
	ComboCooldownTimerHandle.Invalidate();

}*/

/*
void UBossEgyptianAnimInstance::PlayLightAttackCombo() {

	if( !MontageBoxing ) {
		// no montage, nothing to do
		UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::AttackCombo no MontageBoxing, not doing anything") );
		return;
	}

	if( !ComboCooldownTimerHandle.IsValid() ) {
		// combo timer is not running - this means that
		// this is my first attack in combo
		// i want to show animation
		// and start the timer
		
		Montage_Play( MontageBoxing, 1.0f );
		return;

	}
	
	// combo timer is already running
	// this means that i want to extend
	// my previous attack
	// and refresh the timer
	
	UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::AttackCombo start") );

	Montage_Play( MontageHitLight, 1.0f );
	
	UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::AttackCombo end") );

}*/

void UBossEgyptianAnimInstance::PlayIdle() {

	// Continuously plays through idle montage.

	//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PlayIdle") );

	// make sure i have the montage
	if( !MontageIdle ) {
		// no montage, nothing to do
		UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PlayIdle no MontageIdle, not doing anything") );
		return;
	}

	if( Montage_IsPlaying( MontageIdle ) ) {
		// slot occupied, nothing to do
		//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PlayIdle occupied") );
		return;
		
	}
	
	//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PlayIdle ok") );

	// play the montage
	Montage_Play( MontageIdle, 1.0f, EMontagePlayReturnType::Duration, 0.0f, false );

	// but instruct the montage to
	// cycle through the "Default" section perpetually
	Montage_SetNextSection( FName("Default"), FName("Default"), MontageIdle );

}

/*
void UBossEgyptianAnimInstance::PoseSit() {

	// Sits without doing anything.

	//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PlayIdle") );

	// make sure i have the montage
	if( !MontageIdle ) {
		// no montage, nothing to do
		UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PoseSit no MontageIdle, not doing anything") );
		return;
	}
	
	UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PoseSit ok") );
	
	// finish all montages quickly (blend out)
	//StopAllMontages( 0.2f );
	
	// play the montage
	Montage_Play( MontageIdle, 1.0f, EMontagePlayReturnType::Duration, 0.0f, false );

	// run this section once
	// in the montage i specified
	// no auto blend out
	Montage_SetNextSection( FName("Default"), FName("Idle"), MontageIdle );
	Montage_SetNextSection( FName("Idle"), FName("End"), MontageIdle );
	
	UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::PoseSit finished") );

}//*/

/*
void UBossEgyptianAnimInstance::StandUpFromChair() {

	// Transitions from idle to fighting.

	// make sure i have the montage
	if( !MontageIdle ) {
		// no montage, nothing to do
		UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::BeginFight no MontageIdle, not doing anything") );
		return;
	}
	
	//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::BeginFight going from idle") );

	// finish all montages quickly (blend out)
	// help:
	// https://forums.unrealengine.com/t/blend-anim-montage-sections/332654/10
	StopAllMontages( 0.5f );

	// run idle, cycle through sections
	//Montage_SetNextSection( FName("Default"), FName("StandUp"), MontageIdle );
	//Montage_SetNextSection( FName("StandUp"), FName("End"), MontageIdle );

	//UE_LOG( LogTemp, Warning, TEXT("UBossEgyptianAnimInstance::BeginFight finished") );

}//*/

void UBossEgyptianAnimInstance::NativeBeginPlay() {

    // attempt to populate private variable
    OwnerChara = Cast<ACharacter>( TryGetPawnOwner() );

}

void UBossEgyptianAnimInstance::UpdateVariables() {

    // help:
    // https://www.youtube.com/watch?v=kbrTNqG1Uh8&list=PLlswSOADCx3dZuEIYN7dxAwYSKIwNIIC-&t=1325
    // CO2301 Session 10

    if( !OwnerChara ) {
        // no character,
        // reset all public variables
        
        OwnerVelocity = 0.0f;
        OwnerAngle = 0.0f;

        return;
    }

    // get necessary vectors
    OwnerVelocityVector = OwnerChara->GetVelocity();
    OwnerTransform = OwnerChara->GetActorTransform();

    // calculate necessary public variables

    OwnerVelocity = OwnerVelocityVector.Size();

    // help:
    // "Kismet/KismetMathLibrary.h" function InverseTransformDirection
    // https://forums.unrealengine.com/t/get-rotation-from-xvector-c/320487/4
    FVector InversedOwnerTransformDirection = OwnerTransform.InverseTransformVectorNoScale( OwnerVelocityVector );
    OwnerAngle = UKismetMathLibrary::MakeRotFromX( InversedOwnerTransformDirection ).Yaw;

}
