// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEgyptian.h"
#include "Kismet/GameplayStatics.h"
#include "Particle.h"
#include "HoruseusDemoGameModeBase.h"

// Sets default values
ABossEgyptian::ABossEgyptian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossEgyptian::BeginPlay()
{
	Super::BeginPlay();

	// remember gamemode for future use
	CustomGameModeBase = Cast<AHoruseusDemoGameModeBase>( UGameplayStatics::GetGameMode(GetWorld()) );
	
	// player/ai controllers appear only upon begin play - not
	// in the constructor

	// i want to remember this upcasted controller because
	// otherwise i will have to upcast it many times
	CustomAIController = Cast<ABossEgyptianController>( GetController() );
	
	if( CustomAIController ) {
		// i want to do some things if this is my custom boss controller
		
		// listen to the "interact" signal
		// from current custom player controller
		//CustomPlayerController->CurrentGunClasChangedSignatureInstance.AddDynamic( this, &APlayerCharacter::RespondToCurrentGunClasChangedSignatureInstance );

		}
			
	// reused code from MyCharacter

	// remember reference to custom anim instance
	CustomAnimInstance = Cast<UBossEgyptianAnimInstance>( GetMesh()->GetAnimInstance() );

	/*
	// i do this in behavior tree
	if( CustomAnimInstance ) {
		CustomAnimInstance->PlayIdle();
	}*/

}

// Called every frame
void ABossEgyptian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
// Called to bind functionality to input
void ABossEgyptian::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

float ABossEgyptian::TakeDamage( float DamageAmount, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser ) {
	
	UE_LOG( LogTemp, Warning, TEXT("ABossEgyptian::TakeDamage") );

	// apply the damage
	StatsBaseHP -= DamageAmount;

	// decide on what to do next
	if( StatsBaseHP<=0.0f ) {
		// this attack was final - boss is now dead
		
		UE_LOG( LogTemp, Warning, TEXT("ABossEgyptian::TakeDamage final attack, dead") );
		
		if (CustomGameModeBase) {
			CustomGameModeBase->WonGame(true);
		}

		// show animation
		/*if( CustomAnimInstance && MontageDeath ) {
		
			// bind delegates
			// help:
			// https://forums.unrealengine.com/t/play-montage-in-c-with-onblendout-oninterrupted-etc/447184/4
			CustomAnimInstance->OnPlayMontageNotifyEnd.AddDynamic(
				this, &ABossEgyptian::OnMontageHitTakenEnd
				);

			CustomAnimInstance->Montage_Play( MontageDeath, 1.0f );
			// i want to destroy self and
			// change game mode only after animation finishes playing
			//Destroy();

		}*/

	}
	else {
		// this attack is not final - boss is still alive

		UE_LOG( LogTemp, Warning, TEXT("ABossEgyptian::TakeDamage remaining health %f"), StatsBaseHP );

		// show animation
		if( CustomAnimInstance ) 
		{
			CustomAnimInstance->TakeHitLight();
		}
		GetWorld()->SpawnActor<AParticle>(ParticleClass, this->GetActorLocation(), this->GetActorRotation());
	
	} // else final attack..

	return DamageAmount;

}

float ABossEgyptian::GetStatsHP() {

    return StatsBaseHP;

}

float ABossEgyptian::GetStatsDamage() {

    return StatsBaseDamage;

}

void ABossEgyptian::OnMontageHitTakenEnd(
			FName NotifyName,
			const FBranchingPointNotifyPayload& BranchingPointPayload
		) {
		
	UE_LOG( LogTemp, Warning, TEXT("ABossEgyptian::PlayMontageNotifyEnd") );

}

int ABossEgyptian::GetCurrentCustomState() {

    return CurrentCustomState;

}

