// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Sceptor.h"
#include "GameFramework/SpringArmComponent.h"
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

//void AMyCharacter::Fire()
//{
//	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
//
//	if (AnimInstance && AttackMontage)
//	{
//		//if(!AnimInstance && )
//		AnimInstance->Montage_Play(AttackMontage);
//	}
//		UE_LOG(LogTemp, Warning, TEXT("Bullet fired."));
//}

void AMyCharacter::Attack()
{
	if (canMove)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

		if (animInstance && AttackMontage)
		{

			if (!animInstance->Montage_IsPlaying(AttackMontage))
			{
				animInstance->Montage_Play(AttackMontage, 1.0f);
					ScWeapon->canAttack = true;
			}

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


