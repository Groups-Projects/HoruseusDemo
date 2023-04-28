// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "HoruseusDemoGameModeBase.h"
#include "Sceptor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/Pawn.h"
#include "HealthPickUpActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "Particle.h"

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

	//created a spring arm for the minimap that is connected to the root component.
	MiniMapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Mini Map Arm"));
	MiniMapArm->SetupAttachment(RootComponent);
	MiniMapArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	//Created a minimap camera that connects to the minimap spring arm.
	MiniMapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Mini Map Camera"));
	MiniMapCamera->SetupAttachment(MiniMapArm);

	canMove = true;
	health = 100.0f;
	iComboState = 0;
	IsInAttack = false;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ScWeaponClass)
	{
		ScWeapon = GetWorld()->SpawnActor<ASceptor>(ScWeaponClass, this->GetActorLocation(), this->GetActorRotation());
		ScWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Scepter"));
		ScWeapon->SetOwner(this);
	}

	ScWeapon->SetActorRelativeLocation(FVector(.0f, 0.0f, -10.0f));
	ScWeapon->SetActorRelativeRotation(FRotator(0.0f, 100.0f, 0.0f));

	GetWorld()->GetTimerManager().SetTimer(LowerStamina, this, &AMyCharacter::HandleSprinting, 1.0f, true);
	GetWorld()->GetTimerManager().SetTimer(RegenerateStamina, this, &AMyCharacter::RefillStamina, 5.0f, true);
}

void AMyCharacter::MoveForward(float Axis)
{
	if (health >= 0.0f && canMove) 
	{
		AddMovementInput(GetActorForwardVector() * Axis);
	}
}

void AMyCharacter::MoveStrafe(float Axis)
{
	if (health >= 0.0f && canMove) 
	{
		AddMovementInput(GetActorRightVector() * Axis);
	}
}

void AMyCharacter::Turn(float Axis)
{
	if (health >= 0.0f && canMove) 
	{
		AddControllerYawInput(Axis * TurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMyCharacter::LookUp(float Axis)
{
	if (health >= 0.0f && canMove) 
	{
		AddControllerPitchInput(Axis * LookupRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMyCharacter::ActorDestroy()
{
	Destroy();
	ScWeapon->Destroy();
}

void AMyCharacter::HealthPickup()
{
	health += 10.0f;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), CrystalPickUpSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f);
	GEngine->AddOnScreenDebugMessage(-10, 1.0f, FColor::Yellow, "+10 Health");
}

void AMyCharacter::Attack()
{

	if (canMove)
	{
		UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

		if (canMove && !animInstance->Montage_IsPlaying(NULL)) // check if can move and no montage is playing
		{

			switch (AttackNum)
			{
			case 0:
				if (animInstance && AttackMontage)
				{
					if (!animInstance->Montage_IsPlaying(AttackMontage))
					{
						animInstance->Montage_Play(AttackMontage, 1.0f);
						IsInAttack = true;
						ScWeapon->CanAttack = true;
						AttackNum++;
						GetWorldTimerManager().SetTimer(GeneralMontageTimerHandle, this, &AMyCharacter::Attack_End, GeneralMontageTimerValue, false);
						break;
					}

				}
			case 1:
				if (animInstance && AttackMontage_2)
				{
					if (!animInstance->Montage_IsPlaying(AttackMontage_2))
					{
						animInstance->Montage_Play(AttackMontage_2, 1.0f);
						IsInAttack = true;
						ScWeapon->CanAttack = true;
						AttackNum++;
						GetWorldTimerManager().SetTimer(GeneralMontageTimerHandle, this, &AMyCharacter::Attack_End, GeneralMontageTimerValue, false);
						break;
					}
				}
			case 2:
				if (animInstance && AttackMontage_3)
				{
					if (!animInstance->Montage_IsPlaying(AttackMontage_3))
					{
						animInstance->Montage_Play(AttackMontage_3, 1.0f);
						IsInAttack = true;
						ScWeapon->CanAttack = true;
						AttackNum++;
						GetWorldTimerManager().SetTimer(GeneralMontageTimerHandle, this, &AMyCharacter::Attack_End, GeneralMontageTimerValue, false);
						break;
					}
				}
			case 3:
				if (animInstance && AttackMontage)
				{
					if (!animInstance->Montage_IsPlaying(AttackMontage))
					{
						animInstance->Montage_Play(AttackMontage, 1.0f);
						IsInAttack = true;
						ScWeapon->CanAttack = true;
						AttackNum++;
						GetWorldTimerManager().SetTimer(GeneralMontageTimerHandle, this, &AMyCharacter::Attack_End, GeneralMontageTimerValue, false);
						break;
					}

				}
			default:
				AttackNum = 0;

			}

		}
	}
}

void AMyCharacter::Attack_End()
{
	IsInAttack = false;
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (canMove)
	{
		if (health - DamageAmount > 0)
		{
			// am alive
			health -= DamageAmount;
			UE_LOG(LogTemp, Warning, TEXT("Taking Damage.Remaining Health:%f"), health);

			if (animInstance && GetHitMontage)
			{
				// can show montage
				animInstance->Montage_Play(GetHitMontage, 1.0f);
			}
			// bleed
			GetWorld()->SpawnActor<AParticle>(ParticleClass, this->GetActorLocation(), this->GetActorRotation());
		}

		else
		{
			// about to die
			UE_LOG(LogTemp, Warning, TEXT("DEAD"));
			canMove = false;

			if (animInstance && DyingMontage)
			{
				animInstance->Montage_Play(DyingMontage, 1.0f);
			}

			// call appropriate functions, destroy actor, proceed to gameover screen
			FTimerHandle timer;
			GetWorldTimerManager().SetTimer(timer, this, &AMyCharacter::ActorDestroy, 10.0f, false);
			if (IsPlayerControlled())
			{
				Cast<AHoruseusDemoGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GameOver(true);
			}
			else
			{
				Cast<AHoruseusDemoGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->EnemyDestroyed();
			}
			DetachFromControllerPendingDestroy();
		}

	}
	return DamageAmount;
}


void AMyCharacter::Sprint()
{
	if (Stamina > 0)
	{
		bPlayerIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 900.0f;
	}
	else
	{
		StopSprinting();
	}
}

void AMyCharacter::StopSprinting()
{
	bPlayerIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void AMyCharacter::RefillStamina()
{
	if (!bPlayerIsSprinting)
	{
		if (Stamina < 100) {
			if (Stamina + 1.0f < 100.f)
			{
				Stamina = Stamina + 10.0f;
			}
			else
			{
				Stamina = 100.f;
			}
			UE_LOG(LogTemp, Warning, TEXT("PlayerStamina : %f"), Stamina);
		}
	}
}

void AMyCharacter::HandleSprinting()
{
	if (bPlayerIsSprinting)
	{
		if (Stamina - 10.f > 0)
		{
			Stamina -= 10.f;
		}
		else
		{
			Stamina = 0;
			bPlayerIsSprinting = false;
			StopSprinting();
		}
		UE_LOG(LogTemp, Warning, TEXT("PlayerStamina : %f"), Stamina);
	}
}

void AMyCharacter::Crouching()
{
	PlayerCanCrouch = true;
}

void AMyCharacter::StopCrouching()
{
	PlayerCanCrouch = false;
}

float AMyCharacter::ReturnHealth()
{
	return health;
}

float AMyCharacter::ReturnStamina()
{
	return Stamina;
}
