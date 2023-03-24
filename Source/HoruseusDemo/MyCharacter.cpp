// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Sceptor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 300.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	
	canMove = true;
	health = 100.0f;
	iComboState = 0;
	 
}
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//ScWeapon = Cast<ASceptor>(GetOwner());

	if (ScWeaponClass)
	{
		ScWeapon = GetWorld()->SpawnActor<ASceptor>(ScWeaponClass, this->GetActorLocation(), this->GetActorRotation());
		ScWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Scepter"));
		ScWeapon->SetOwner(this);
	}
}


void AMyCharacter::MoveForward(float Axis)
{
	if (health >= 0.0f) {
		AddMovementInput(GetActorForwardVector() * Axis);
	}
}

void AMyCharacter::MoveStrafe(float Axis)
{
	if (health >= 0.0f) {
		AddMovementInput(GetActorRightVector() * Axis);
	}
}

void AMyCharacter::Turn(float Axis)
{
	if (health >= 0.0f) {
		AddControllerYawInput(Axis);
	}
}

void AMyCharacter::LookUp(float Axis)
{
	if (health >= 0.0f) {
		AddControllerPitchInput(Axis);
	}
}

void AMyCharacter::GeneralMontageTimerHandleRanOut() {

	// I end up here when I wait too long after
	// attacking, so my combo breaks
	// and the character goes back to the idle state.

	// become idle
	iComboState = 0;

	// invalidate timer
	// so it can be set again
	GeneralMontageTimerHandle.Invalidate();

}

void AMyCharacter::Attack_1()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

	// make sure i have animation montage to show
	if( !(animInstance && AttackMontage) )
	{
		// no montage, nothing to do
		return;
	}

	if (!animInstance->Montage_IsPlaying(AttackMontage))
	{
		// montage was not playling

		// perform an attack
		animInstance->Montage_Play(AttackMontage, 1.0f);
		ScWeapon->canAttack = true;

		// set combo state
		iComboState = 1;

		// start combo breaker timer
		GetWorldTimerManager().SetTimer(GeneralMontageTimerHandle, this, &AMyCharacter::GeneralMontageTimerHandleRanOut, GeneralMontageTimerValue, true, 2.0f);
			
	}
}

void AMyCharacter::Attack_2()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

	if (animInstance && AttackMontage_2)
	{

		if (!animInstance->Montage_IsPlaying(AttackMontage_2))
		{
			// perform an attack
			animInstance->Montage_Play(AttackMontage_2, 1.0f);
			ScWeapon->canAttack = true;
			
			// set combo state
			iComboState = 2;

			// start combo breaker timer
			GetWorldTimerManager().SetTimer(GeneralMontageTimerHandle, this, &AMyCharacter::GeneralMontageTimerHandleRanOut, GeneralMontageTimerValue, true, 2.0f);

		}

	}
}



void AMyCharacter::Attack()
{

	int state_idle = 0;
	int state_atk1 = 1;
	int state_atk2 = 2;

	if (canMove)
	{

		if ( !GeneralMontageTimerHandle.IsValid() )
			// im not in a combo chain
			// because combo timer is invalid
		{

			// so i want to perform first attack
			Attack_1();
			return;
		}

		// i end up here only if im in a combo

		if (iComboState == state_idle) 
		{
			Attack_1();
				

		}
		else if (iComboState == state_atk1) 
		{


		}
		else if (iComboState == state_atk2) {


		}
		else {
		}

		
	}
}


float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Taking Damage"));

	if (health <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DEAD"));
		Destroy();
		ScWeapon->Destroy();
	}

	return DamageAmount;
}


