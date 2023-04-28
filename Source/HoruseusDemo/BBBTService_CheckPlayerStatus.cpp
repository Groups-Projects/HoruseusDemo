// Fill out your copyright notice in the Description page of Project Settings.


#include "BBBTService_CheckPlayerStatus.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

// reused code from CO2301 assignment 1

bool UBBBTService_CheckPlayerStatus::PlayerIsInFrontOfMe( APawn *SelfPawn, APawn *LivePawn ) {

    // This function detects that the player's pawn is in front
    // of my enemy pawn. The distance / actual visibility
    // of player pawn are still questionable.

    // If I want to implement stealth mechanics, I will
    // switch from APawn to my custom
    // upcasted pawn.

	// reused code from CO2301 lab

    // vector from this enemy to player
    FVector BetweenThisEnemyAndPlayerVector 
        = LivePawn->GetActorLocation() - SelfPawn->GetActorLocation();
    BetweenThisEnemyAndPlayerVector.Normalize();

    // where is this enemy facing
    FVector ThisEnemyForwardVector = SelfPawn->GetActorForwardVector();
    
    // compute the dot product
    float CosinusBetweenCurrentDirectionAndPlayer = FVector::DotProduct(
        BetweenThisEnemyAndPlayerVector, ThisEnemyForwardVector
    );

    // make sure player is in front of me
    bool bPlayerIsInFrontOfMe = CosinusBetweenCurrentDirectionAndPlayer>=0.0f;
    if( !bPlayerIsInFrontOfMe ) {
        return false;
    }

    //UE_LOG( LogTemp, Warning, TEXT("dot product is: %f"), CosinusBetweenCurrentDirectionAndPlayer );

    return true;

}

void UBBBTService_CheckPlayerStatus::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) {

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTService_PlayerLocation.cpp

    Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );
    
    //-------------------------+++
    // Preparations.
    
    //UE_LOG( LogTemp, Warning, TEXT("UBehTreeS_CheckPlayerStatus::TickNode") );

    // i will use Live instead of Player to avoid accidental name
    // clashes

    // get normal and upcasted controllers
    AAIController *SelfController = OwnerComp.GetAIOwner();
    APlayerController *LiveController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
    
    // get normal and upcasted pawns
    APawn* SelfPawn = SelfController->GetPawn();
    APawn* LivePawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );
    
    // make sure i have blackboard
    UBlackboardComponent *SelfBlackboardComp = OwnerComp.GetBlackboardComponent();
    if( !SelfBlackboardComp ) {
        return;
        }

    // remember starting location only once
    if( !SelfBlackboardComp->IsVectorValueSet( TEXT("StartingPoint") ) ) {
        SelfBlackboardComp->SetValueAsVector( TEXT("StartingPoint"), SelfPawn->GetActorLocation() );
    }

    if( !LivePawn ) {
        // player pawn does not exist, possibly destroyed
        // because player died
        // nothing to do
        SelfBlackboardComp->SetValueAsBool( TEXT("PlayerDied"), true );
        return;
    }

    // make sure i can see player unobstructed
    bool bIHaveLineOfSight = SelfController->LineOfSightTo( LivePawn );
    bool bPlayerIsInFrontOfMe = PlayerIsInFrontOfMe( SelfPawn, LivePawn );
    
    //-------------------------+++
    // Actual code.

    if( !( bIHaveLineOfSight && bPlayerIsInFrontOfMe ) ) {
        // oh no, something is blocking the player!

        // set appropriate blackboard
        
        // help:
        // https://docs.unrealengine.com/5.1/en-US/BlueprintAPI/AI/Components/Blackboard/ClearValue/
        
        // i rely on 'blackboard value is set'
        // so it does not matter if it's true or false:
        // as long as it is set, behaviour tree will act
        // the same
        // so i have to clear it
        //SelfBlackboardComp->ClearValue( TEXT("CanSeePlayer") );
        
        // this is no longer the case
        // i need true and faluse values

        SelfBlackboardComp->SetValueAsBool( TEXT("CanSeePlayer"), false );

        return;

    }

    // i can clearly see the player

    SelfBlackboardComp->SetValueAsBool( TEXT("CanSeePlayer"), true );

    // remember several things about him
    SelfBlackboardComp->SetValueAsVector( TEXT("LastPlayerLocation"), LivePawn->GetActorLocation() );
    
}