// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEgyptianController.h"

// reused code from CO2301 assignment 1

ABossEgyptianController::ABossEgyptianController() {

    // i need tick if i want characters
    // to rotate when they move
    // help:
    // https://forums.unrealengine.com/t/behavior-trees-rotate-to-face-bb-entry-and-moveto-can-never-work-together-reasonably/378431/6
    PrimaryActorTick.bCanEverTick = true;

}

void ABossEgyptianController::Tick( float DeltaTime ) {

    Super::Tick( DeltaTime );

}

void ABossEgyptianController::BeginPlay() {

    Super::BeginPlay();

    if( CustomBehaviorTree ) {
        UE_LOG( LogTemp, Warning, TEXT("CustomBehaviorTree ok") );
        RunBehaviorTree( CustomBehaviorTree );
    }

}