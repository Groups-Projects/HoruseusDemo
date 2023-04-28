// Fill out your copyright notice in the Description page of Project Settings.


#include "BBBTTask_LookAtPlayer.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBBBTTask_LookAtPlayer::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) {

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTTask_Shoot.cpp

	Super::ExecuteTask( OwnerComp, NodeMemory );
    
    //UE_LOG( LogTemp, Warning, TEXT("UBehTreeS_CheckPlayerStatus::TickNode") );
    
    // make sure i have blackboard
    UBlackboardComponent *SelfBlackboardComp = OwnerComp.GetBlackboardComponent();
    if( !SelfBlackboardComp ) {
        // task failed
        return EBTNodeResult::Failed;
        }

    // get necessary meshes and controllers
    // i will use Live instead of Player to avoid accidental name
    // clashes

    AAIController *SelfController = OwnerComp.GetAIOwner();
    USkeletalMeshComponent *SelfMesh = SelfController->GetCharacter()->GetMesh();
    APlayerController *LiveController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
    USkeletalMeshComponent *LiveMesh = LiveController->GetCharacter()->GetMesh();
	
    // rotate own head to face the player

    int32 HeadBoneIndex = SelfMesh->GetBoneIndex( FName("Head") );
    FTransform SelfHeadTransform = SelfMesh->GetBoneTransform( HeadBoneIndex ); //, EBoneSpaces::WorldSpace );
    
    // help:
    // https://forums.unrealengine.com/t/blueprint-getting-an-object-to-look-at-another-object/363332/3
    FVector Direction = LiveMesh->GetForwardVector(); // FVector::ForwardVector;
    FRotator LookAtRotator = FRotationMatrix::MakeFromX(Direction).Rotator();
    SelfHeadTransform.SetRotation( LookAtRotator.Quaternion() );

	return EBTNodeResult::Succeeded;

}
